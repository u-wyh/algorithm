#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MOD = 201314;

int n,m;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN<<1];
int toq[MAXN<<1];
int idq[MAXN<<1];
int opq[MAXN<<1];
int cntq=1;

int son[MAXN];
int sz[MAXN];
int fa[MAXN];
int dep[MAXN];
int dfncnt;
int dfn[MAXN];
int top[MAXN];

int ans[MAXN];

int len[MAXN<<2];
int sum[MAXN<<2];
int tag[MAXN<<2];

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

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline void addEdge(int u,int v,int w,int op){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=w;
    opq[cntq]=op;
    headq[u]=cntq++;
}

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    sz[u]=1;
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v,u);
        sz[u]+=sz[v];
        if(son[u]==0||sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]&&v!=fa[u]){
            dfs2(v,v);
        }
    }
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void up(int i){
    sum[i]=(sum[i<<1]+sum[i<<1|1])%MOD;
}

void lazy(int i,int v){
    sum[i]=(sum[i]+len[i]*v)%MOD;
    tag[i]=(tag[i]+v)%MOD;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,1);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        ans%=MOD;
        return ans;
    }
}

void update(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            swap(x,y);
        }
        update(dfn[top[x]],dfn[x],1,n,1);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    update(dfn[y],dfn[x],1,n,1);
}

int query(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            swap(x,y);
        }
        ans+=query(dfn[top[x]],dfn[x],1,n,1);
        x=fa[top[x]];
        ans%=MOD;
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    ans+=query(dfn[y],dfn[x],1,n,1);
    ans%=MOD;
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=2;i<=n;i++){
        int u=read()+1;
        addedge(u,i);
    }
    for(int i=1;i<=m;i++){
        int l,r,z;
        l=read()+1,r=read()+1,z=read()+1;
        addEdge(r,z,i,1);
        addEdge(l-1,z,i,-1);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=n;i++){
        update(i,1);
        for(int ei=headq[i];ei;ei=nxtq[ei]){
            int v=toq[ei];
            ans[idq[ei]]+=opq[ei]*query(1,v);
            ans[idq[ei]]%=MOD;
        }
    }

    for(int i=1;i<=m;i++){
        ans[i]=(ans[i]%MOD+MOD)%MOD;
        printf("%d\n",ans[i]);
    }
    return 0;
}
/*
5 2
0
0
1
1
1 4 3
1 4 2
*/