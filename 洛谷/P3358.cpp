#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXV = 505*2;
const int MAXE = 1e5;
const int INF = 1e9;

int n,m,k,s,t;
int len[MAXN];
int lt[MAXN];
int rt[MAXN];
int arr[MAXV];

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

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>lt[i]>>rt[i];
        arr[2*i-1]=lt[i];
        arr[2*i]=rt[i];
    }
    sort(arr+1,arr+2*n+1);
    m=1;
    for(int i=2;i<=2*n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        len[i]=rt[i]-lt[i];
        lt[i]=find(lt[i]);
        rt[i]=find(rt[i]);
    }
    s=m+1,t=s+1;
    for(int i=1;i<=n;i++){
        addedge(lt[i],rt[i],1,-len[i]);
    }
    addedge(s,1,k,0);
    addedge(m,t,k,0);
    for(int i=1;i<m;i++){
        addedge(i,i+1,k,0);
    }
    mincostmaxflow();
    cout<<-mincost<<endl;
    return 0;
}