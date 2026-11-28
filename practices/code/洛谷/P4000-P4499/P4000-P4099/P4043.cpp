// https://www.luogu.com.cn/problem/P4043
// 题意：第一行输入剧情点数 N，接下来 N 行描述剧情点 i（1 到 N）：
// 先输入出边数 K_i
// 随后输入 K_i 对 (b_{i,j}, t_{i,j})
// 表示可前往剧情点 b_{i,j} 且耗时 t_{i,j}。
// 游戏图是有向无环图且所有点从 1 可达；
// 玩家从 1 出发，可随时重开游戏回到 1。
// 输出看完所有支线剧情（即经过图中每一条边至少一次）所需的最少总时间。
// 数据范围：对于 100% 的数据，N <= 300，
// 0 <= K_i <= 50，1 <= t_{i,j} <= 300
// sum(K_i) <= 5000。
// 难度评分：2600（洛谷分级换算）
// 算法标签：最小费用最大流、上下界网络流
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;
const int MAXV = MAXN;
const int MAXE = 120*MAXN;
const int INF = 1e9;

int n, m, s, t;
int ans;
int mincost, maxflow;
int in[MAXN];

int pot[MAXV];
int dis[MAXV];
int pre[MAXV];         
bool vis[MAXV];

queue<int> q;
bool inqueue[MAXV];

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

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

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
    inqueue[s] = true;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = false;

        for(int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = cap[i];     // 剩余容量
            int c = cost[i];    // 单位费用

            if(w > 0 && pot[u] + c < pot[v]) {
                pot[v] = pot[u] + c;  // 更新势能

                if(!inqueue[v]) {
                    q.push(v);
                    inqueue[v] = true;
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

        maxflow += flow;
        mincost += flow * (dis[t] + pot[t]);

        for(int u = t; u != s; u = to[pre[u] ^ 1]) {
            cap[pre[u]] -= flow;      // 正向边减流量
            cap[pre[u] ^ 1] += flow;  // 反向边加流量
        }

        for(int i = 1; i <= t; i++) {
            if(dis[i] < INF) {
                pot[i] += dis[i];  // 关键：更新势能
            }
        }
    }
}

int main()
{
    n=read();
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        int k=read();
        for(int j=1;j<=k;j++){
            int b,t;
            b=read(),t=read();
            addedge(i,b,INF,t);
            in[b]++;
            in[i]--;
            ans+=t;
        }
    }
    for(int i=2;i<=n;i++){
        addedge(i,1,INF,0);
    }
    for(int i=1;i<=n;i++){
        if(in[i]>0){
            addedge(s,i,in[i],0);
        }
        else if(in[i]<0){
            addedge(i,t,-in[i],0);
        }
    }
    mincostmaxflow();
    cout<<(ans+mincost)<<endl;
    return 0;
}