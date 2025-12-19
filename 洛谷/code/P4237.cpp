#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 15005;
const int MAXV = 605;
const int MAXE = 1e6+5;
const int INF = 1e9;

int n,m,a,b,s,t;
int ans;

int val[MAXN];
// int cost[305];
int pos1[305];
int pos2[305];

int headg[MAXN];
int nxtg[MAXM<<1];
int tog[MAXM<<1];
int weightg[MAXM<<1];
int cntg=1;

int idcnt;
int id[MAXN];
int dist[305][MAXN];

int mincost, maxflow;
int pot[MAXV]; 
int dis[MAXV];
int pre[MAXV];
bool vis[MAXV];

queue<int>q;
bool in[MAXV];

int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int cap[MAXE];
int cost[MAXE];
int cnt = 2;

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

inline void addedgeg(int u,int v,int w){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    weightg[cntg]=w;
    headg[u]=cntg++;
}

struct cmp {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.first > b.first;  // 按距离从小到大排序
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> heap;

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

bool visit[MAXN];
struct node{
    int u;
    int d;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>hp;

void dijkstra(int s,int *dis){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        visit[i]=false;
    }
    dis[s]=val[s];
    hp.push({s,dis[s]});
    while(!hp.empty()){
        int u=hp.top().u;
        hp.pop();
        if(visit[u]){
            continue;
        }
        visit[u]=true;
        for(int i=headg[u];i;i=nxtg[i]){
            int v=tog[i];
            int w=weightg[i];
            if(dis[v]>dis[u]+w+val[v]){
                dis[v]=dis[u]+w+val[v];
                hp.push({v,dis[v]});
            }
        }
    }
}

int main()
{
    n=read(),m=read(),a=read(),b=read();
    s=a+b+1,t=s+1;
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedgeg(u,v,w);
        addedgeg(v,u,w);
    }

    for(int i=1;i<=a;i++){
        int val=read();
        pos1[i]=read();
        addedge(s,i,1,val);
    }
    for(int i=1;i<=b;i++){
        int val=read();
        ans+=val;
        pos2[i]=read();
        addedge(i+a,t,1,0);
    }

    for(int i=1;i<=a;i++){
        int sub;
        if(id[pos1[i]]){
            sub=id[pos1[i]];
        }
        else{
            id[pos1[i]]=++idcnt;
            sub=idcnt;
            dijkstra(pos1[i],dist[idcnt]);
        }
        for(int j=1;j<=b;j++){
            if(dist[sub][pos2[j]]<INF){
                addedge(i,j+a,1,dist[sub][pos2[j]]);
            }
        }
    }
    mincostmaxflow();
    if(maxflow!=b){
        cout<<"No"<<endl<<maxflow<<endl;
    }
    else{
        cout<<"Yes"<<endl<<(ans-mincost)<<endl;
    }
    return 0;
}