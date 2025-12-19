#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,q;

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

int tree[MAXN<<2];
bool change[MAXN<<2];
int val[MAXN<<2];

int fa[MAXN];
int sz[MAXN];
int son[MAXN];
int dep[MAXN];
int dfncnt;
int top[MAXN];
int dfn[MAXN];

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    fa[u]=f;
    dep[u]=dep[f]+1;
    sz[u]=1;
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
    change[i]=false;
    if(l==r){
        tree[i]=0;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void lazy(int i,int v){
    change[i]=true;
    val[i]=v;
    tree[i]=v;
}

void down(int i){
    if(change[i]){
        lazy(i<<1,val[i]);
        lazy(i<<1|1,val[i]);
        change[i]=false;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(pos<=mid){
            return query(pos,l,mid,i<<1);
        }
        else{
            return query(pos,mid+1,r,i<<1|1);
        }
    }
}

void pathupdate(int x, int y, int v) {
    while (top[x] != top[y]) {
        if (dep[top[x]] <= dep[top[y]]) {
            update(dfn[top[y]], dfn[y], v, 1, n, 1);
            y = fa[top[y]];
        } else {
            update(dfn[top[x]], dfn[x], v, 1, n, 1);
            x = fa[top[x]];
        }
    }
    update(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    q=read();
    for(int i=1;i<=q;i++){
        int op,u;
        op=read(),u=read();
        if(op==1){
            update(dfn[u],dfn[u]+sz[u]-1,1,1,n,1);
        }
        else if(op==2){
            pathupdate(u,1,0);
        }
        else{
            printf("%d\n",query(dfn[u],1,n,1));
        }
    }
    return 0;
}