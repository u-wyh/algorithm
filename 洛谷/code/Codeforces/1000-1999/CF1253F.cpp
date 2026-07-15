#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;
const int MAXK = 2e5+5;
const int MAXH = 20;
const long long INF = 1e18;

int n,m,k,q;

int cnt=2;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
bool visit[MAXM<<1];

struct edge{
    int u,v;
    long long w;
}nums[MAXM];

int fa[MAXK];
int dep[MAXK];
int st[MAXK][MAXH];

int cntk=1;
int headk[MAXK];
int nxtk[MAXK];
int tok[MAXK];
long long key[MAXK];
int cntu;

struct cmp{
    bool operator()(pair<int,long long>a,pair<int,long long>b){
        return a.second>b.second;
    }
};
long long dis[MAXN];
bool vis[MAXN];
priority_queue<pair<int,long long>,vector<pair<int,long long>>,cmp>heap;

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

bool comp(edge a,edge b){
    return a.w<b.w;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

inline void addEdge(int u,int v){
    nxtk[cntk]=headk[u];
    tok[cntk]=v;
    headk[u]=cntk++;
}

void dijkstra(){
    for(int i=k+1;i<=n;i++){
        dis[i]=INF;
    }
    for(int i=1;i<=k;i++){
        heap.push({i,0});
    }
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void kruskalRebuild(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    cntu=n;
    for(int i=1;i<=m;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            cntu++;
            fa[fx]=cntu;
            fa[fy]=cntu;
            fa[cntu]=cntu;
            key[cntu]=nums[i].w;
            addEdge(cntu,fx);
            addEdge(cntu,fy);
        }
    }
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=headk[u];i;i=nxtk[i]){
        int v=tok[i];
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=MAXH-1;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int main()
{
    n=read(),m=read(),k=read(),q=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
        nums[i].u=u;
        nums[i].v=v;
        nums[i].w=w;
    }
    dijkstra();
    for(int i=1;i<=m;i++){
        nums[i].w=dis[nums[i].u]+dis[nums[i].v]+nums[i].w;
    }
    sort(nums+1,nums+m+1,comp);
    kruskalRebuild();
    dfs(cntu,0);
    for(int i=1;i<=q;i++){
        int u,v;
        u=read(),v=read();
        printf("%lld\n",key[lca(u,v)]);
    }
    return 0;
}