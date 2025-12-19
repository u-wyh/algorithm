#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 20;
const int MAXV = MAXN*MAXN;
const int MAXE = 1e5;
const int INF = 1e15;

int a,b,n,m,s,t;
int mincost, maxflow;

int id[MAXN][MAXN];
// int val1[MAXN][MAXN];
// int val2[MAXN][MAXN];

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
    // 初始化势能为无穷大
    for(int i = 1; i <= t; i++) {
        pot[i] = INF;
    }

    // 源点入队
    q.push(s);
    pot[s] = 0;
    in[s] = true;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        in[u] = false;

        // 遍历所有出边
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

signed main()
{
    cin>>a>>b>>n>>m;
    int total=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            id[i][j]=++total;
        }
    }
    s=total+1;
    t=s+1;

    for(int i=0;i<=n;i++){
        for(int j=0;j<m;j++){
            int val;
            cin>>val;
            addedge(id[i][j],id[i][j+1],1,-val);
            addedge(id[i][j],id[i][j+1],INF,0);
        }
    }
    for(int j=0;j<=m;j++){
        for(int i=0;i<n;i++){
            int val;
            cin>>val;
            addedge(id[i][j],id[i+1][j],1,-val);
            addedge(id[i][j],id[i+1][j],INF,0);
        }
    }
    for(int i=1;i<=a;i++){
        int k,x,y;
        cin>>k>>x>>y;
        addedge(s,id[x][y],k,0);
    }
    
    for(int i=1;i<=b;i++){
        int k,x,y;
        cin>>k>>x>>y;
        addedge(id[x][y],t,k,0);
    }

    mincostmaxflow();
    cout<<-mincost<<endl;
    return 0;
}