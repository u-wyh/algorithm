// https://www.luogu.com.cn/problem/P4452
#include<bits/stdc++.h>
using namespace std;
#define int long long  // 使用 long long 类型
const int MAXN = 505;   // 最大节点数
const int MAXM = 5e4+5;   // 最大边数（正向+反向）
const int INF = 1e18;     // 无穷大值

int n, m,K,T;          // 节点数、边数、源点、汇点
int s,t;
int mincost, maxflow;     // 最小费用和最大流量

int g[205][205];
int f[205][205];
int query[205][5];
int inq[205],out[205];

// 势能数组（Johnson算法核心）
int pot[MAXN];           // 用于调整边权，消除负权边影响

// Dijkstra算法相关
int dis[MAXN];           // 最短距离数组
int pre[MAXN];           // 前驱边索引
bool vis[MAXN];          // 访问标记

// SPFA算法相关
queue<int> q;            // SPFA队列
bool in[MAXN];           // 节点是否在队列中

// 链式前向星存图
int head[MAXN];          // 每个节点的第一条边
int nxt[MAXM];           // 下一条边索引
int to[MAXM];            // 目标节点
int cap[MAXM];           // 边容量
int cost[MAXM];          // 单位费用
int cnt = 2;             // 边计数器（从2开始，方便异或取反向边）

// 优先队列比较器（小顶堆）
struct cmp {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.first > b.first;  // 按距离从小到大排序
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> heap;

// 快速读入函数
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

// 添加边函数
inline void addedge(int u, int v, int w, int c) {
    // 正向边：u->v
    nxt[cnt] = head[u];
    to[cnt] = v;
    cap[cnt] = w;
    cost[cnt] = c;
    head[u] = cnt++;
    
    // 反向边：v->u (容量为0，费用为负)
    nxt[cnt] = head[v];
    to[cnt] = u;
    cap[cnt] = 0;
    cost[cnt] = -c;
    head[v] = cnt++;
}

// SPFA初始化势函数（处理负权边）
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
    // 初始化距离和前驱
    for(int i = 1; i <= n; i++) {
        dis[i] = INF;
        pre[i] = -1;
        vis[i] = false;
    }
    
    // 源点入堆
    dis[s] = 0;
    heap.push({0, s});
    
    while(!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        
        // 如果已访问，跳过
        if(vis[u]) continue;
        vis[u] = true;
        
        // 遍历所有出边
        for(int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int residual = cap[i];   // 保存原始容量
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
    return dis[t] < INF;  // 判断是否找到增广路径
}

// 最小费用最大流主函数
void mincostmaxflow() {
    // 步骤1: 初始化势函数（处理负权边）
    spfa(s);
    maxflow = 0;
    mincost = 0;
    
    // 步骤2: 循环寻找增广路径
    while(dijkstra()) {
        // 步骤3: 计算增广路径上的最小容量
        int flow = INF;
        for(int u = t; u != s; u = to[pre[u] ^ 1]) {
            flow = min(flow, cap[pre[u]]);
        }
        
        // 步骤4: 更新流量和费用
        maxflow += flow;
        // 实际费用 = 调整后距离 + 汇点势能
        mincost += flow * (dis[t] + pot[t]);
        
        // 步骤5: 更新路径上的边容量
        for(int u = t; u != s; u = to[pre[u] ^ 1]) {
            cap[pre[u]] -= flow;      // 正向边减流量
            cap[pre[u] ^ 1] += flow;  // 反向边加流量
        }
        
        // 步骤6: 更新势函数（为下一轮准备）
        for(int i = 1; i <= n; i++) {
            if(dis[i] < INF) {
                pot[i] += dis[i];  // 关键：更新势能
            }
        }
    }
}

signed main() 
{
    n=read(),m=read(),K=read(),T=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g[i][j]=read();
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=read();
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<5;j++){
            query[i][j]=read();
        }
    }
    s=1,t=2;
    int s0=3,t0=4;
    int id=4;
    for(int i=1;i<=m;i++){
        inq[i]=++id;
        out[i]=++id;
    }
    n=id;

    addedge(s,s0,K,0);
    addedge(t0,t,K,0);
    addedge(s0,t0,K,0);
    for(int i=1;i<=m;i++){
        addedge(inq[i],out[i],1,-query[i][4]);
    }
    for(int i=1;i<=m;i++){
        int a=query[i][0]+1;
        int st=query[i][2];
        if(g[1][a]<=st){
            addedge(s0,inq[i],1,f[1][a]);
        }
        int b=query[i][1]+1;
        int et=query[i][3];
        if(et+g[b][1]<=T){
            addedge(out[i],t0,1,f[b][1]);
        }
    }
    for(int i=1;i<=m;i++){
        int b=query[i][1]+1;
        int et=query[i][3];
        for(int j=1;j<=m;j++){
            int a=query[j][0]+1;
            int st=query[j][2];
            if(et+g[b][a]<=st){
                addedge(out[i],inq[j],1,f[b][a]);
            }
        }
    }

    mincostmaxflow();
    cout<<(-mincost)<<endl;
    return 0;
}