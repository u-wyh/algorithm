// https://www.luogu.com.cn/problem/P3381
// 最小费用最大流问题是每条边有流量  并且每条边的流量有单位价格
// 要在满足流量最大的情况下  使得花费最小的解决方案
// 时间复杂度O(F×(V+E)logV) f为最大流值
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e3+5;
const int MAXM = 1e5+5;
const int INF = 1e18;

int n, m, s, t;
int mincost, maxflow;

// 势能数组（Johnson算法核心）
int pot[MAXN];           // 用于调整边权，消除负权边影响

int dis[MAXN];
int pre[MAXN];           // 前驱边索引
bool vis[MAXN];

queue<int> q;
bool in[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cap[MAXM];
int cost[MAXM];
int cnt = 2;

struct cmp {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.first > b.first;  // 按距离从小到大排序
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> heap;

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

signed main()
{
    // 读入节点数、边数、源点、汇点
    n = read(), m = read(), s = read(), t = read();

    // 读入并添加所有边
    for(int i = 1; i <= m; i++) {
        int u, v, w, c;
        u = read(), v = read(), w = read(), c = read();
        addedge(u, v, w, c);
    }

    // 计算最小费用最大流
    mincostmaxflow();

    // 输出最大流量和最小费用
    cout << maxflow << ' ' << mincost << endl;

    return 0;
}