// https://www.luogu.com.cn/problem/P7130
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n;
int val[MAXN];
int sz[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int sum[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
int fa[MAXN];
int root[MAXN];
int all[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int merge(int i,int j){
    if(i==0||j==0){
        return i+j;
    }
    if(val[i]>val[j]){
        swap(i,j);
    }
    rs[i]=merge(rs[i],j);
    sum[i]=sum[ls[i]]+sum[rs[i]]+val[i];
    all[i]=all[ls[i]]+all[rs[i]]+1;
    if(dist[ls[i]]<dist[rs[i]]){
        swap(ls[i],rs[i]);
    }
    dist[i]=dist[rs[i]]+1;
    fa[ls[i]]=fa[rs[i]]=i;
    return i;
}

int pop(int i){
    fa[ls[i]]=ls[i];
    fa[rs[i]]=rs[i];
    fa[i]=merge(ls[i],rs[i]);
    ls[i]=rs[i]=dist[i]=0;
    return fa[i];
}

void dfs(int u,int f){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
            sz[u]+=sz[v];
            root[u]=merge(root[u],root[v]);
        }
    }
    while(all[root[u]]>(sz[u]/2)){
        root[u]=pop(root[u]);
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        ls[i]=rs[i]=dist[i]=0;
        fa[i]=i;
        sum[i]=val[i];
        root[i]=i;
        all[i]=1;
    }
    dist[0]=-1;
    dfs(1,0);
    cout<<sum[root[1]]<<endl;
    return 0;
}