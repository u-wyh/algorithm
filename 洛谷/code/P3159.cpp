#include<bits/stdc++.h>
using namespace std;
const int MAXN = 25;
const int MAXV = 1e3+5;
const int MAXM = 5e4+5;
const int INF = 1e9;

int n,m,s,t;
int walk[8][2]={{1,-1},{1,0},{1,1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};

int mincost, maxflow;

int pot[MAXV];

int dis[MAXV];
int pre[MAXV];
bool vis[MAXV];

queue<int> q;
bool in[MAXV];

int head[MAXV];
int nxt[MAXM];
int to[MAXM];
int cap[MAXM];
int cost[MAXM];
int cnt = 2;

int start[MAXN][MAXN];
int over[MAXN][MAXN];
int limit[MAXN][MAXN];

struct cmp {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.first > b.first;  // 按距离从小到大排序
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
            int w = cap[i];     // 剩余容量
            int c = cost[i];    // 单位费用

            // 如果有容量且可以松弛
            if(w > 0 && pot[u] + c < pot[v]) {
                pot[v] = pot[u] + c;  // 更新势能

                // 如果节点v不在队列中，加入队列
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

            // 跳过容量为0的边
            if(residual <= 0) continue;

            // 使用势函数调整边权（关键步骤）
            int adjusted_cost = c_original + pot[u] - pot[v];

            // 如果可以松弛
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

int id(int x,int y){
    return (x-1)*m+y;
}

int main()
{
    cin>>n>>m;

    int white1=0;
    int white2=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            start[i][j]=c-'0';
            if(start[i][j]){
                white1++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            over[i][j]=c-'0';
            if(over[i][j]){
                white2++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            limit[i][j]=c-'0';
        }
    }

    if(white1!=white2){
        cout<<-1<<endl;
        return 0;
    }

    s=2*n*m+1,t=s+1;

    int flow=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(start[i][j]&&!over[i][j]){
                addedge(s,id(i,j),1,0);
                flow++;
            }
            if(over[i][j]&&!start[i][j]){
                addedge(id(i,j)+n*m,t,1,0);
            }

            int f=limit[i][j]/2;
            if((limit[i][j]%2)&&(start[i][j]^over[i][j])){
                f++;
            }
            addedge(id(i,j),id(i,j)+n*m,f,0);

            for(int k=0;k<8;k++){
                int x=i+walk[k][0];
                int y=j+walk[k][1];
                if(x>=1&&x<=n&&y>=1&&y<=m){
                    addedge(id(i,j)+n*m,id(x,y),INF,1);
                }
            }
        }
    }

    mincostmaxflow();

    if(maxflow!=flow){
        cout<<-1<<endl;
    }
    else{
        cout<<mincost<<endl;
    }
    return 0;
}