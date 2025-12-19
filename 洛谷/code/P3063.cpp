#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int val[MAXN<<1];
int cnt=1;
int n,m,k;
int vis[MAXN][MAXN];
int ans=INT_MAX;

void addedge(int u,int v,int w,int y){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    val[cnt]=y;
    head[u]=cnt++;
}

void dfs(int u,int w,int v){
    if(w+v>ans){
        return ;
    }
    if(u==n){
        ans=min(ans,w+v);
    }
    for(int i=head[u];i;i=Next[i]){
        int e=to[i];
        if(vis[u][e])
            continue;
        vis[u][e]=1;
        dfs(e,w+weight[i],max(v,val[i]));
        vis[u][e]=0;
    }
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w,y;
        cin>>u>>v>>w>>y;
        addedge(u,v,w,k/y);
        addedge(v,u,w,k/y);
    }
    dfs(1,0,0);
    cout<<ans<<endl;
    return 0;
}
