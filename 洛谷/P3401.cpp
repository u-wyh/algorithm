#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;

int n,q;
int eorval[MAXN];
int val[MAXN];

int all;
int res[10];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int dep[MAXN];
int sz[MAXN];
int top[MAXN];
int son[MAXN];
int dfn[MAXN];
int seg[MAXN];
int fa[MAXN];
int dfncnt;

int tree[MAXN<<2][10];
int tag[MAXN<<2];
int len[MAXN<<2];

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    fa[u]=f;
    dep[u]=dep[f]+1;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            eorval[v]=eorval[u]^w;
            val[v]=w;
            dfs1(v,u);
            sz[u]+=sz[v];
            if(son[u]==0||sz[son[u]]<sz[v]){
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
        if(v!=son[u]&&v!=fa[u]){
            dfs2(v,v);
        }
    }
}

void up(int i){
    for(int k=0;k<10;k++){
        tree[i][k]=tree[i<<1][k]+tree[i<<1|1][k];
    }
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        int v=eorval[seg[l]];
        for(int k=0;k<10;k++){
            if((v>>k)&1){
                tree[i][k]=1;
            }
            else{
                tree[i][k]=0;
            }
        }
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int val){
    tag[i]^=val;
    for(int k=0;k<10;k++){
        if(val&(1<<k)){
            tree[i][k]=len[i]-tree[i][k];
        }
    }
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        for(int k=0;k<10;k++){
            res[k]+=tree[i][k];
        }
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

void query(int x,int y){
    for(int i=0;i<10;i++){
        res[i]=0;
    }
    all=0;

    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        all+=dfn[x]-dfn[top[x]]+1;
        query(dfn[top[x]],dfn[x],1,n,1);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    all+=dfn[x]-dfn[y]+1;
    query(dfn[y],dfn[x],1,n,1);
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=q;i++){
        int op,u,v,w;
        op=read(),u=read(),v=read();
        if(op==1){
            query(u,v);
            long long ans=0;
            for(int k=0;k<10;k++){
                ans+=1ll*(res[k]*(all-res[k]))*(1<<k);
            }
            cout<<ans<<endl;
        }
        else{
            w=read();
            if(dep[u]<dep[v]){
                swap(u,v);
            }
            int delta=w^val[u];
            val[u]=w;
            update(dfn[u],dfn[u]+sz[u]-1,delta,1,n,1);
        }
    }
    return 0;
}