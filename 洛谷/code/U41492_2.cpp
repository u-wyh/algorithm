#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];
int ans[MAXN];
int cnt[MAXN];
int kind;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int son[MAXN];
int fa[MAXN];
int sz[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u,int f){
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[son[u]]<sz[v]){
                son[u]=v;
            }
        }
    }
}

void effect(int u){
    cnt[val[u]]++;
    if(cnt[val[u]]==1){
        kind++;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]){
            effect(v);
        }
    }
}

void cancel(int u){
    cnt[val[u]]--;
    if(cnt[val[u]]==0){
        kind--;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]){
            cancel(v);
        }
    }
}

void dfs2(int u,int keep){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,0);
        }
    }
    if(son[u]){
        dfs2(son[u],1);
    }

    cnt[val[u]]++;
    if(cnt[val[u]]==1){
        kind++;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]&&v!=fa[u])
            effect(v);
    }
    ans[u]=kind;
    if(keep==0){
        cancel(u);
    }
}

void compute(){
    dfs1(1,0);
    dfs2(1,1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    compute();

    cin>>m;
    for(int i=1;i<=m;i++){
        int u;
        cin>>u;
        cout<<ans[u]<<endl;
    }
    return 0;
}