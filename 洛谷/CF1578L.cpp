#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 1e5+5;
const int MAXK = MAXN*2;

int n,m;

int val[MAXN];

struct edge{
    int u,v,w;
}nums[MAXM];

int cntu;
int fa[MAXK];
long long sum[MAXK];
long long ans[MAXK];
int key[MAXK];
int cnt=1;
int ls[MAXK];
int rs[MAXK];
int head[MAXK];
int nxt[MAXK];
int to[MAXK];

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

bool cmp(edge a,edge b){
    return a.w>b.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
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
            fa[fx]=++cntu;
            fa[fy]=cntu;
            fa[cntu]=cntu;
            ls[cntu]=fx,rs[cntu]=fy;
            key[cntu]=nums[i].w;
            addedge(cntu,fx);
            addedge(cntu,fy);
        }
    }
}

void dfs(int u){
    if(u>n){
        dfs(ls[u]);
        dfs(rs[u]);
        sum[u]=sum[ls[u]]+sum[rs[u]];
        ans[u]=max(min(key[u]-sum[ls[u]],ans[rs[u]]-sum[ls[u]]),min(key[u]-sum[rs[u]],ans[ls[u]]-sum[rs[u]]));
    }
    else{
        sum[u]=val[u];
        ans[u]=INT_MAX;
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].u=read();
        nums[i].v=read();
        nums[i].w=read();
    }
    sort(nums+1,nums+m+1,cmp);
    kruskalRebuild();
    dfs(cntu);
    if(ans[cntu]<=0){
        cout<<-1<<endl;
    }
    else{
        cout<<ans[cntu]<<endl;
    }
    return 0;
}