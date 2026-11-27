// https://www.luogu.com.cn/problem/P3171
// 题意：输入路由器数量 n、双向链路数 m，每条链路连接的路由器 u, v 及距离 w，以及 1 到 n 号路由器各自的吞吐量 c_i。
// 所有数据包都从 1 号点沿最短路径转发到 n 号点，起点 1 和终点 n 吞吐量不限（且不存在 1 与 n 的直连边）
// 中间每个路由器每秒最多转发 c_i 个数据包，链路带宽无限。
// 输出从路由器 1 到路由器 n 的最大网络吞吐量。
// 数据范围：1 <= n <= 500，1 <= m <= 10^5，1 <= w, c_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：最大流、Dijkstra
using namespace std;
#define int long long
const int MAXN = 505;
const int MAXM = 1e5+5;
const int MAXT = MAXN*2;
const int MAXE = MAXM*10;
const int INF = 1e18;

int n,m,s,t;
int val[MAXN];

int headg[MAXN];
int nxtg[MAXM<<1];
int tog[MAXM<<1];
int weightg[MAXM<<1];
int cntg=1;

int dis1[MAXN];
// int dis2[MAXN];
bool vis[MAXN];

int in[MAXN];
int out[MAXN];

struct node{
    int pos,dis;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.dis>b.dis;
    }
};
priority_queue<node,vector<node>,compare>heap;

int dep[MAXT];
int iter[MAXT];

int head[MAXT];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];
int cnt=2;

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

inline void addEdge(int u,int v,int w){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    weightg[cntg]=w;
    headg[u]=cntg++;
}

void dijkstra(int s,int *dis){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        vis[i]=false;
    }
    dis[s]=0;
    heap.push({s,0});
    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        int u=tmp.pos;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=headg[u];i;i=nxtg[i]){
            int v=tog[i];
            int w=weightg[i];
            if(dis[v]>dis[u]+w){
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
}

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    now[cnt]=0;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    head[v]=cnt++;
}

bool bfs(){
    for(int i=1;i<=t;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;
}

int dfs(int u,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;
                flow+=d;
                f-=d;
                if(f==0){
                    break;
                }
            }
        }
    }
    return flow;
}

int maxflow(){
    int flow=0;
    while(bfs()){
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dijkstra(1,dis1);
    // dijkstra(n,dis2);

    s=1,t=2*n;
    for(int i=1;i<=n;i++){
        in[i]=i;
        out[i]=i+n;
    }

    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    addedge(in[1],out[1],INF);
    addedge(in[n],out[n],INF);
    for(int i=2;i<n;i++){
        addedge(in[i],out[i],val[i]);
    }

    for(int u=1;u<=n;u++){
        for(int i=headg[u];i;i=nxtg[i]){
            int v=tog[i];
            int w=weightg[i];
            // if(dis1[u]+w+dis2[v]==dis1[n]){
            //     addedge(out[u],in[v],INF);
            // }
            if(dis1[u]+w==dis1[v]){
                addedge(out[u],in[v],INF);
            }
        }
    }

    int flow=maxflow();
    cout<<flow<<endl;
    return 0;
}