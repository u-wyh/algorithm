#include<bits/stdc++.h>
using namespace std;
const int MAXN = 25;
const int MAXV = 2000;
const int MAXE = 1e5;
const int INF = 1e9;

int n,m,s,t,total;
int val[MAXN][MAXN<<1];
int node[MAXN][MAXN<<1];
int mincost, maxflow;

int pot[MAXV];

int dis[MAXV];
int pre[MAXV];
bool vis[MAXV];

queue<int> q;
bool in[MAXV];

int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int cap[MAXE];
int cost[MAXE];
int cnt = 2;

struct cmp {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.first > b.first;
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> heap;

inline void addedge(int u, int v, int w, int c) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    cap[cnt] = w;
    cost[cnt] = c;
    head[u] = cnt++;

    nxt[cnt] = head[v];
    to[cnt] = u;
    cap[cnt] = 0;
    cost[cnt] = -c;
    head[v] = cnt++;
}

void spfa(int s) {
    for(int i = 1; i <= t; i++) {
        pot[i] = INF;
    }

    q.push(s);
    pot[s] = 0;
    in[s] = true;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        in[u] = false;

        for(int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = cap[i];
            int c = cost[i];

            if(w > 0 && pot[u] + c < pot[v]) {
                pot[v] = pot[u] + c;

                if(!in[v]) {
                    q.push(v);
                    in[v] = true;
                }
            }
        }
    }
}

bool dijkstra() {
    for(int i = 1; i <= t; i++) {
        dis[i] = INF;
        pre[i] = -1;
        vis[i] = false;
    }

    dis[s] = 0;
    heap.push({0, s});

    while(!heap.empty()) {
        int u = heap.top().second;
        heap.pop();

        if(vis[u]) continue;
        vis[u] = true;

        for(int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int residual = cap[i];
            int c_original = cost[i]; // 保存原始费用

            if(residual <= 0) continue;

            int adjusted_cost = c_original + pot[u] - pot[v];

            if(dis[u] + adjusted_cost < dis[v]) {
                dis[v] = dis[u] + adjusted_cost;
                pre[v] = i;  // 记录前驱边索引
                heap.push({dis[v], v});
            }
        }
    }
    return dis[t] < INF;
}

void mincostmaxflow() {
    spfa(s);
    maxflow = 0;
    mincost = 0;

    while(dijkstra()) {
        // 计算增广路径上的最小容量
        int flow = INF;
        for(int u = t; u != s; u = to[pre[u] ^ 1]) {
            flow = min(flow, cap[pre[u]]);
        }

        //  更新流量和费用
        maxflow += flow;
        // 实际费用 = 调整后距离 + 汇点势能
        mincost += flow * (dis[t] + pot[t]);

        // 更新路径上的边容量
        for(int u = t; u != s; u = to[pre[u] ^ 1]) {
            cap[pre[u]] -= flow;      // 正向边减流量
            cap[pre[u] ^ 1] += flow;  // 反向边加流量
        }

        //  更新势函数（为下一轮准备）
        for(int i = 1; i <= t; i++) {
            if(dis[i] < INF) {
                pot[i] += dis[i];  // 关键：更新势能
            }
        }
    }
}

void buildgraph1(){
    for(int i=1;i<=t;i++){
        head[i]=0;
    }
    cnt=2;

    for(int i=1;i<=m;i++){
        addedge(s,node[1][i],1,0);
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            addedge(node[i][j],node[i][j]+total,1,-val[i][j]);
        }
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<=m+i-1;j++){
            addedge(node[i][j]+total,node[i+1][j],1,0);
            addedge(node[i][j]+total,node[i+1][j+1],1,0);
        }
    }

    for(int j=1;j<=n+m-1;j++){
        addedge(node[n][j]+total,t,1,0);
    }
}

void buildgraph2(){
    for(int i=1;i<=t;i++){
        head[i]=0;
    }
    cnt=2;

    for(int i=1;i<=m;i++){
        addedge(s,node[1][i],1,0);
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            addedge(node[i][j],node[i][j]+total,INF,-val[i][j]);
        }
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<=m+i-1;j++){
            addedge(node[i][j]+total,node[i+1][j],1,0);
            addedge(node[i][j]+total,node[i+1][j+1],1,0);
        }
    }

    for(int j=1;j<=n+m-1;j++){
        addedge(node[n][j]+total,t,INF,0);
    }
}

void buildgraph3(){
    for(int i=1;i<=t;i++){
        head[i]=0;
    }
    cnt=2;

    for(int i=1;i<=m;i++){
        addedge(s,node[1][i],1,0);
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            addedge(node[i][j],node[i][j]+total,INF,-val[i][j]);
        }
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<=m+i-1;j++){
            addedge(node[i][j]+total,node[i+1][j],INF,0);
            addedge(node[i][j]+total,node[i+1][j+1],INF,0);
        }
    }

    for(int j=1;j<=n+m-1;j++){
        addedge(node[n][j]+total,t,INF,0);
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            cin>>val[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            node[i][j]=++total;
        }
    }
    s=total*2+1;
    t=s+1;

    buildgraph1();
    mincostmaxflow();
    cout<<-mincost<<endl;

    buildgraph2();
    mincostmaxflow();
    cout<<-mincost<<endl;

    buildgraph3();
    mincostmaxflow();
    cout<<-mincost<<endl;
    return 0;
}