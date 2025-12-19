#include<bits/stdc++.h>
using namespace std;
const int MAXN = 85;
const int MAXV = 2*MAXN;
const int MAXE = MAXN*MAXN*10;
const int INF = 1e9;

int n,s,t;
int val[MAXN][MAXN];
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
        return a.first > b.first;  // 按距离从小到大排序
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> heap;

int match[MAXN];

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

// Dijkstra寻找增广路径
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
        for(int i = 1; i <= t; i++) {
            if(dis[i] < INF) {
                pot[i] += dis[i];  // 关键：更新势能
            }
        }
    }
}

void init(){
    cnt=2;
    for(int i=1;i<=t;i++){
        head[i]=0;
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>val[i][j];
        }
    }
    s=2*n+1,t=s+1;
    for(int i=1;i<=n;i++){
        addedge(s,i,1,0);
    }
    for(int i=1;i<=n;i++){
        addedge(i+n,t,1,0);
    }
    // int now=cnt;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            addedge(i,j+n,1,-val[i][j]);
        }
    }
    mincostmaxflow();
    cout<<-mincost<<endl;
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v>n&&v<=2*n&&cap[i]==0){
                // cout<<v<<' ';
                match[u]=v-n;
                break;
            }
        }
    }

    int ans=-mincost;
    vector<pair<int,int>>res;
    for(int b=1;b<=n;b++){
        int g=match[b];
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==b&&j==g){
                    continue;
                }
                addedge(i,j+n,1,-val[i][j]);
            }
        }
        for(int i=1;i<=n;i++){
            addedge(s,i,1,0);
        }
        for(int i=1;i<=n;i++){
            addedge(i+n,t,1,0);
        }
        mincostmaxflow();
        int val=-mincost;
        if(val<ans){
            res.push_back({b,g});
        }
    }
    sort(res.begin(),res.end());
    for(int i=0;i<(int)res.size();i++){
        cout<<res[i].first<<' '<<res[i].second<<endl;
    }
    return 0;
}