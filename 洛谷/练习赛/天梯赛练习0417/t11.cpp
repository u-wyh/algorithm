#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int sz=0;
int depth=0;
int root;
int fa[MAXN];
int dep[MAXN];
bool vis[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>fa[i];
        if(fa[i]==-1){
            root=i;
        }
        else{
            addedge(fa[i],i);
        }
    }
    dfs(root,0);
    while(m--){
        int u;
        cin>>u;
        while(u!=-1&&!vis[u]){
            vis[u]=1;
            sz++;
            depth=max(depth,dep[u]);
            u=fa[u];
        }
        cout<<(sz*2-1-depth)<<endl;
    }
    return 0;
}