#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = MAXN*MAXN;
const int MAXV = 2*MAXN;
const int MAXE = 10*MAXM;
const int INF = 1e9;

int n,m,s,t;
string str[MAXN];
map<string,int>mp;

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

void dfs1(int u){
    cout<<str[u]<<endl;
    vis[u]=true;
    for(int i=head[u+n];i;i=nxt[i]){
        int v=to[i];
        if(v<=n&&cap[i]==0){
            dfs1(v);
            break;
        }
    }
}

void dfs2(int u){
    vis[u]=true;
    for(int i=head[u+n];i;i=nxt[i]){
        int v=to[i];
        if(v<=n&&cap[i]==0&&!vis[v]){
            dfs2(v);
        }
    }
    cout<<str[u]<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>str[i];
        mp[str[i]]=i;
    }
    s=2*n+1,t=2*n+2;

    addedge(1,n+1,2,-1);
    addedge(n,n*2,2,-1);

    for(int i=2;i<n;i++){
        addedge(i,i+n,1,-1);
    }

    bool flag=false;
    for(int i=1;i<=m;i++){
        string s1,s2;
        cin>>s1>>s2;
        int u=mp[s1],v=mp[s2];
        if(u>v){
            swap(u,v);
        }
        if(u==1&&v==n){
            flag=true;
        }
        addedge(u+n,v,1,0);
    }
    addedge(s,1,2,0);
    addedge(2*n,t,2,0);
    mincostmaxflow();
    if(maxflow==2){
        cout<<(-mincost-2)<<endl;
        dfs1(1);
        dfs2(1);
    }
    else if(maxflow==1&&flag){
        // 这是最特殊的情况  如果flag为1  那么说明一定会存在符合条件的  直达的
        // 尽管这种方案存在  沃恩尽量不用 因为到达的城市很少
        // 其他的直达航班是不能做来回的  但是这个1到n n到1 的是可以直达的
        cout<<2<<endl;
        cout<<str[1]<<endl<<str[n]<<endl<<str[1]<<endl;
    }
    else{
        cout<<"No Solution!"<<endl;
    }
    return 0;
}