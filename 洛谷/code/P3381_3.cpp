#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e3+5;
const int MAXM = 1e5+5;
const int INF = 1e10;

int n,m,s,t;
int mincost,maxflow;

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
int cnt=2;

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

inline void addedge(int u,int v,int w,int c){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    cost[cnt]=c;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    cost[cnt]=-c;
    head[v]=cnt++;
}

void spfa(int s){
    for(int i=1;i<=n;i++){
        pot[i]=INF;
    }

    q.push(s);
    pot[s]=0;
    in[s]=true;

    while(!q.empty()){
        int u=q.front();
        q.pop();
        in[u]=false;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int c=cost[i];

            if(w>0&&pot[u]+c<pot[v]){
                pot[v]=pot[u]+c;
                if(!in[v]){
                    q.push(v);
                    in[v]=true;
                }
            }
        }
    }
}

struct cmp{
    bool operator()(pair<int,int>a,pair<int,int>b){
        return a.first>b.first;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

bool dijkstra(){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        pre[i]=-1;
        vis[i]=false;
    }

    dis[s]=0;
    heap.push({0,s});

    while(!heap.empty()){
        int u=heap.top().second;
        heap.pop();

        if(vis[u]){
            continue;
        }
        vis[u]=true;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(cap[i]<=0){
                continue;
            }

            int adjusted=cost[i]+pot[u]-pot[v];
            if(dis[u]+adjusted<dis[v]){
                dis[v]=dis[u]+adjusted;
                pre[v]=i;
                heap.push({dis[v],v});
            }
        }
    }
    return dis[t]<INF;
}

void mincostmaxflow(){
    spfa(s);
    while(dijkstra()){
        int flow=INF;
        for(int u=t;u!=s;u=to[pre[u]^1]){
            flow=min(flow,cap[pre[u]]);
        }

        maxflow+=flow;
        mincost+=flow*(dis[t]+pot[t]);

        for(int u=t;u!=s;u=to[pre[u]^1]){
            cap[pre[u]]-=flow;
            cap[pre[u]^1]+=flow;
        }

        for(int i=1;i<=n;i++){
            if(dis[i]<INF){
                pot[i]+=dis[i];
            }
        }
    }
}

signed main()
{
    n=read(),m=read(),s=read(),t=read();
    for(int i=1;i<=m;i++){
        int u,v,w,c;
        u=read(),v=read(),w=read(),c=read();
        addedge(u,v,w,c);
    }
    mincostmaxflow();
    cout<<maxflow<<' '<<mincost<<endl;
    return 0;
}