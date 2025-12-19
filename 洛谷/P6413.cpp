#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1505;
const int MAXM = 5005;
const int INF = 1e9;
const int MOD = 1e9+7;

int n,m;
struct Edge{
    int u,v,w;
};
Edge edge[MAXM];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int ans[MAXM];

int dis[MAXN];
bool vis[MAXN];
int cntfrom[MAXN];
int cntto[MAXN];

int nums[MAXN];

struct node{
    int pos,dis;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.dis>b.dis;
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

void dijkstra(int s){
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

bool cmp(int a,int b){
    return dis[a]<dis[b];
}

void compute(int s){
    dijkstra(s);

    for(int i=1;i<=n;i++){
        nums[i]=i;
    }
    sort(nums+1,nums+n+1,cmp);

    for(int i=1;i<=n;i++){
        cntfrom[i]=0;
        cntto[i]=0;
    }
    cntfrom[s]=1;

    for(int i=1;i<=n;i++){
        int u=nums[i];
        if(dis[u]==INF){
            break;
        }
        for(int ei=head[u];ei;ei=nxt[ei]){
            int v=to[ei];
            int w=weight[ei];
            if(dis[v]==dis[u]+w){
                cntfrom[v]=(cntfrom[v]+cntfrom[u])%MOD;
            }
        }
    }

    for(int i=n;i>=1;i--){
        int u=nums[i];
        cntto[u]=1;
        if(dis[u]==INF){
            continue;
        }
        for(int ei=head[u];ei;ei=nxt[ei]){
            int v=to[ei];
            int w=weight[ei];
            if(dis[v]==dis[u]+w){
                cntto[u]=(cntto[v]+cntto[u])%MOD;
            }
        }
    }

    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;
        int w=edge[i].w;
        if(dis[u]!=INF&&dis[v]!=INF&&dis[u]+w==dis[v]){
            ans[i]=(ans[i]+cntfrom[u]*cntto[v]%MOD)%MOD;
        }
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        edge[i]={u,v,w};
    }

    for(int i=1;i<=n;i++){
        compute(i);
    }

    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}