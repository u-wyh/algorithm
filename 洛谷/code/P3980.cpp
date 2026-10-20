// https://www.luogu.com.cn/problem/P3980
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1005;
const int MAXM = 5e5+5;
const int INF = 1ll<<60;

int n,m,s,t;
int mincost;
int maxflow;
int need[MAXN];

int pot[MAXN];
int dis[MAXN];
int pre[MAXN];
bool vis[MAXN];
queue<int>q;
bool in[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cap[MAXM];
int cost[MAXM];
int cntg=2;

inline void addedge(int u,int v,int w,int c){
    nxt[cntg]=head[u];
    to[cntg]=v;
    cap[cntg]=w;
    cost[cntg]=c;
    head[u]=cntg++;

    nxt[cntg]=head[v];
    to[cntg]=u;
    cap[cntg]=0;
    cost[cntg]=-c;
    head[v]=cntg++;
}

struct cmp {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.first > b.first;  // 按距离从小到大排序
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> heap;


void spfa(int s) {
    // 初始化势能为无穷大
    for(int i = 1; i <= n; i++) {
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

// Dijkstra寻找增广路径
bool dijkstra() {
    for(int i = 1; i <= n; i++) {
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

// 最小费用最大流主函数
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
        for(int i = 1; i <= n; i++) {
            if(dis[i] < INF) {
                pot[i] += dis[i];  // 关键：更新势能
            }
        }
    }
}


// void mincostmaxflow(){
//     spfa(s);
//     maxflow=0;
//     mincost=0;
//     while(diskstra()){
//         int flow=INF;
//         for(int u=t;u!=s;u=to[pre[u]^1]){
//             flow=min(flow,cap[pre[u]]);
//         }
//         maxflow+=flow;
//         int pathcost=0;
//         for(int u=t;u!=s;u=to[pre[u]^1]){
//             pathcost+=cost[pre[u]];

//         }
//     }
// }

signed main()
{
    int days;
    cin>>days>>m;
    s=days+2;
    t=s+1;
    n=t;

    for(int i=1;i<=days;i++){
        cin>>need[i];
    }
    for(int i=1;i<=days+1;i++){
        int diff=need[i]-need[i-1];
        if(diff>0){
            addedge(s,i,diff,0);
        }
        else if(diff<0){
            addedge(i,t,-diff,0);
        }
    }
    for(int i=1;i<=days;i++){
        addedge(i+1,i,INF,0);
    }
    for(int i=1;i<=m;i++){
        int l,r,c;
        cin>>l>>r>>c;
        addedge(l,r+1,INF,c);
    }

    mincostmaxflow();
    cout<<mincost<<endl;
    return 0;
}