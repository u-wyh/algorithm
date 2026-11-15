// https://www.luogu.com.cn/problem/P3359
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int val[MAXN];

int u[MAXN];
int v[MAXN];
int w[MAXN];

int ord[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int fa[MAXN];
int sz[MAXN];
unordered_map<int,int>mp[MAXN];

long long ans[MAXN];
long long sum=0;

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            val[v]=val[u]^weight[i];
            dfs(v,u);
        }
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void merge(int u,int v){
    u=find(u);
    v=find(v);
    if(sz[u]>sz[v]){
        swap(u,v);
    }
    for(auto p:mp[u]){
        int val=p.first;
        int c=p.second;
        auto it=mp[v].find(val);
        if(it!=mp[v].end()){
            sum+=1ll*c*(it->second);
        }
    }
    for(auto p:mp[u]){
        mp[v][p.first]+=p.second;
    }
    mp[u].clear();
    fa[u]=v;
    sz[v]+=sz[u];
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>u[i]>>v[i]>>w[i];
        addedge(u[i],v[i],w[i]);
        addedge(v[i],u[i],w[i]);
    }
    for(int i=1;i<n;i++){
        cin>>ord[i];
    }

    dfs(1,0);

    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
        mp[i][val[i]]=1;
    }

    ans[n]=0;
    for(int i=n-1;i>=1;i--){
        merge(u[ord[i]],v[ord[i]]);
        ans[i]=sum;
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}