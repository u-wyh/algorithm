#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXV = 22;

int n;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int weight[MAXN];
int cnt=1;

int top[MAXN];
int sz[MAXN];
int son[MAXN];
int dep[MAXN];
int val[MAXN];

int maxdep[1<<MAXV];
int ans[MAXN];

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs1(int u,int fa){
    sz[u]=1;
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        val[v]=val[u]^(1<<w);
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]){
            son[u]=v;
        }
    }
}

void cancel(int u){
    maxdep[val[u]]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        cancel(v);
    }
}

void effect(int u){
    maxdep[val[u]]=max(maxdep[val[u]],dep[u]);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        effect(v);
    }
}

void compute(int u,int t){
    if(maxdep[val[u]]){
        ans[t]=max(ans[t],maxdep[val[u]]+dep[u]-2*dep[t]);
    }
    for(int i=0;i<22;i++){
        if(maxdep[val[u]^(1<<i)]){
            ans[t]=max(ans[t],maxdep[val[u]^(1<<i)]+dep[u]-2*dep[t]);
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        compute(v,t);
    }
}

void dfs2(int u,int keep){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            dfs2(v,0);
            ans[u]=max(ans[u],ans[v]);
        }
    }
    if(son[u]!=0){
        dfs2(son[u],1);
        ans[u]=max(ans[u],ans[son[u]]);
    }

    if(maxdep[val[u]]){
        ans[u]=max(ans[u],maxdep[val[u]]-dep[u]);
    }
    for(int i=0;i<22;i++){
        if(maxdep[val[u]^(1<<i)]){
            ans[u]=max(ans[u],maxdep[val[u]^(1<<i)]-dep[u]);
        }
    }

    maxdep[val[u]]=max(maxdep[val[u]],dep[u]);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            compute(v,u);
            effect(v);
        }
    }
    if(keep==0){
        cancel(u);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<n;i++){
        int u;
        char c;
        cin>>u>>c;
        addedge(u,i+1,c-'a');
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}