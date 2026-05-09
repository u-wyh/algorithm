#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;
const int MOD = 998244353;

int n,m,k;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int idq[MAXN];
int cntq=1;

int dep[MAXN];
int sz[MAXN];
int son[MAXN];
int fa[MAXN];
int top[MAXN];
int dfn[MAXN];
int seg[MAXN];
int dfncnt;

int ans[MAXN];

int power[MAXN];
int val[MAXN];

int tree[MAXN<<2];
int lazy[MAXN<<2];
int sum[MAXN<<2];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void addedgeq(int u,int v,int id){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=id;
    headq[u]=cntq++;
}

int compute(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans*=a;
            ans%=MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void dfs1(int u,int f){
    fa[u]=f;
    sz[u]=1;
    dep[u]=dep[f]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v,u);
        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

void dfs2(int u,int t){
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    top[u]=t;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            dfs2(v,v);
        }
    }
}

void build(int l,int r,int i){
    if(l==r){
        sum[i]=val[seg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        sum[i]=(sum[i<<1]+sum[i<<1|1])%MOD;
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        power[i]=compute(i,k);
    }

    dfs1(1,0);
    dfs2(1,1);

    for(int i=1;i<=n;i++){
        val[i]=(power[dep[i]]-power[dep[i]-1]+MOD)%MOD;
    }
    build(1,n,1);
}

void up(int i){
    tree[i]=(tree[i<<1]+tree[i<<1|1])%MOD;
}

void addlazy(int i,int x){
    tree[i]=(tree[i]+((sum[i]*x)%MOD+MOD))%MOD;
    lazy[i]+=x;
}

void down(int i){
    if(lazy[i]){
        addlazy(i<<1,lazy[i]);
        addlazy(i<<1|1,lazy[i]);
        lazy[i]=0;
    }
}

void add(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,1);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
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
        ans=((ans%MOD)+MOD)%MOD;
        return ans;
    }
}

void add(int x){
    while(x){
        add(dfn[top[x]],dfn[x],1,n,1);
        x=fa[top[x]];
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=query(dfn[top[x]],dfn[x],1,n,1);
        ans%=MOD;
        x=fa[top[x]];
    }
    ans=(ans%MOD+MOD)%MOD;
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa;
        addedge(fa,i);
    }

    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        addedgeq(x,y,i);
    }

    prepare();

    for(int u=1;u<=n;u++){
        add(u);
        for(int ei=headq[u];ei;ei=nxtq[ei]){
            int id=idq[ei];
            int y=toq[ei];
            ans[id]=query(y);
        }
    }
    
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}