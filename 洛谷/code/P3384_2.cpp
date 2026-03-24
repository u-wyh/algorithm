#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m,root,mod;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int sz[MAXN];
int top[MAXN];
int son[MAXN];
int dep[MAXN];
int fa[MAXN];

int len[MAXN<<2];
long long sum[MAXN<<2];
long long tag[MAXN<<2];

void dfs1(int u,int f){
    sz[u]=1;
    fa[u]=f;
    dep[u]=dep[f]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(son[u]==0||sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

void up(int x){
    sum[x]=(sum[x<<1]+sum[x<<1|1])%mod;
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        sum[i]=val[seg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void addlazy(int x,int v){
    tag[x]=(tag[x]+v)%mod;
    sum[x]=(sum[x]+len[x]*v)%mod;
}

void down(int i){
    addlazy(i<<1,tag[i]);
    addlazy(i<<1|1,tag[i]);
    tag[i]=0;
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,jobv);
    }
    else{
        down(i);
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int ans=0;
        down(i);
        int mid=(l+r)>>1;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        ans=(ans+mod)%mod;
        return ans;
    }
}

void pathadd(int x,int y,int v){
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            add(dfn[top[x]],dfn[x],v,1,n,1);
            x=fa[top[x]];
        }
        else{
            add(dfn[top[y]],dfn[y],v,1,n,1);
            y=fa[top[y]];
        }
    }
    add(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),v,1,n,1);
}

int pathsum(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            ans+=query(dfn[top[x]],dfn[x],1,n,1);
            x=fa[top[x]];
        }
        else{
            ans+=query(dfn[top[y]],dfn[y],1,n,1);
            y=fa[top[y]];
        }
        ans%=mod;
    }
    ans+=query(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),1,n,1);
    ans=(ans+mod)%mod;
    return ans;
}

void subtreeadd(int x,int v){
    add(dfn[x],dfn[x]+sz[x]-1,v,1,n,1);
}

int subtreesum(int x){
    return query(dfn[x],dfn[x]+sz[x]-1,1,n,1);
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>root>>mod;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        val[i]%=mod;
    }

    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    dfs1(root,0);
    dfs2(root,root);
    build(1,n,1);

    for(int i=1;i<=m;i++){
        int op,x,y,z;
        cin>>op;
        if(op==1){
            cin>>x>>y>>z;
            pathadd(x,y,z);
        }
        else if(op==2){
            cin>>x>>y;
            cout<<pathsum(x,y)<<endl;
        }
        else if(op==3){
            cin>>x>>y;
            subtreeadd(x,y);
        }
        else{
            cin>>x;
            cout<<subtreesum(x)<<endl;
        }
    }
    return 0;
}