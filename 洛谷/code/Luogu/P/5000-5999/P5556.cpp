#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int BIT = 30;

int n,q;

int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

//线段树
int tree[MAXN<<2];
int tag[MAXN<<2];

//树链剖分
int fa[MAXN];
int sz[MAXN];
int dep[MAXN];
int son[MAXN];
int top[MAXN];
int dfn[MAXN];
int seg[MAXN];
int dfncnt;

//线性基
int basis[32];

bool flag;

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    sz[u]=1;
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
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
    seg[dfncnt]=u;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==son[u]||v==fa[u]){
            continue;
        }
        dfs2(v,v);
    }
}

void lazy(int i,int v){
    tree[i]^=v;
    tag[i]^=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=val[seg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(pos<=mid){
            return query(pos,l,mid,i<<1);
        }
        else{
            return query(pos,mid+1,r,i<<1|1);
        }
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
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>=dep[top[y]]){
            x=fa[top[x]];
        }
        else{
            y=fa[top[y]];
        }
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    return y;
}

void pathupdate(int x,int y,int v){
    while(top[x]!=top[y]){
        if(dep[top[x]]>=dep[top[y]]){
            update(dfn[top[x]],dfn[x],v,1,n,1);
            x=fa[top[x]];
        }
        else{
            update(dfn[top[y]],dfn[y],v,1,n,1);
            y=fa[top[y]];
        }
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    update(dfn[y],dfn[x],v,1,n,1);
}

void insert(int val){
    if(val==0){
        flag=true;
        return ;
    }
    for(int i=BIT;i>=0&&val;i--){
        if(((val>>i)&1)==0){
            continue;
        }
        if(basis[i]==0){
            basis[i]=val;
            break;
        }
        else{
            val^=basis[i];
        }
    }
    if(val==0){
        flag=true;
    }
}

void compute(int x,int y){
    int lcaxy=lca(x,y);
    if(dep[x]+dep[y]-2*dep[lcaxy]+1>=32){
        printf("YES\n");
        return ;
    }

    for(int i=0;i<=31;i++){
        basis[i]=0;
    }
    flag=false;

    while(x!=lcaxy){
        insert(query(dfn[x],1,n,1));
        x=fa[x];
    }
    if(flag){
        printf("YES\n");
        return ;
    }

    while(y!=lcaxy){
        insert(query(dfn[y],1,n,1));
        y=fa[y];
    }
    if(flag){
        printf("YES\n");
        return ;
    }

    insert(query(dfn[lcaxy],1,n,1));
    if(flag){
        printf("YES\n");
        return ;
    }
    else{
        printf("NO\n");
    }
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=q;i++){
        string op;
        int u,v,w;
        cin>>op;
        u=read(),v=read();
        if(op[0]=='U'){
            w=read();
            pathupdate(u,v,w);
        }
        else{
            compute(u,v);
        }
    }
    return 0;
}