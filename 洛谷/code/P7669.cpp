#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const long long INF = 1e18;

int n,m,S,T,U,V;

long long ds[MAXN];
long long dt[MAXN];
long long du[MAXN];
long long dv[MAXN];
bool vis[MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cnt=1;

int head1[MAXN];
int in1[MAXN];
int nxt1[MAXM];
int to1[MAXM];
int cnt1=1;

int head2[MAXN];
int in2[MAXN];
int nxt2[MAXM];
int to2[MAXM];
int cnt2=1;

long long low1[MAXN];
long long low2[MAXN];

struct node{
    int u;
    long long d;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

inline void addedge1(int u,int v){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
    in1[v]++;
}

inline void addedge2(int u,int v){
    nxt2[cnt2]=head2[u];
    to2[cnt2]=v;
    head2[u]=cnt2++;
    in2[v]++;
}

void dijkstra(int s,long long *dis){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        vis[i]=false;
    }
    dis[s]=0;
    heap.push({s,0});
    while(!heap.empty()){
        int u=heap.top().u;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    S=read(),T=read(),U=read(),V=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(S,ds);
    dijkstra(T,dt);
    dijkstra(U,du);
    dijkstra(V,dv);

    long long dis=ds[T];

    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(ds[u]+dt[v]+w==dis){
                addedge1(u,v);
                addedge2(v,u);
            }
        }
    }

    for(int i=1;i<=n;i++){
        low1[i]=du[i];
        low2[i]=du[i];
    }
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(in1[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head1[u];i;i=nxt1[i]){
            int v=to1[i];
            in1[v]--;
            low1[v]=min(low1[v],low1[u]);
            if(in1[v]==0){
                q.push(v);
            }
        }
    }
    
    for(int i=1;i<=n;i++){
        if(in2[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head2[u];i;i=nxt2[i]){
            int v=to2[i];
            in2[v]--;
            low2[v]=min(low2[v],low2[u]);
            if(in2[v]==0){
                q.push(v);
            }
        }
    }

    long long ans=du[V];
    for(int i=1;i<=n;i++){
        ans=min(ans,min(low1[i]+dv[i],low2[i]+dv[i]));
    }
    cout<<ans<<endl;
    return 0;
}