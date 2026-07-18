#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int mostl[MAXN];

int pa[MAXN];
int dep[MAXN];
int son[MAXN];
int sz[MAXN];
int top[MAXN];
int dfn[MAXN];
int seg[MAXN];
int dfncnt;

int maxval[MAXN<<2];
int addtag[MAXN<<2];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u,int fa){
    sz[u]=1;
    pa[u]=fa;
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]){
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
        if(v!=son[u]&&v!=pa[u]){
            dfs2(v,v);
        }
    }
}

void upSeg(int i){
    maxval[i]=max(maxval[i<<1],maxval[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        maxval[i]=dep[seg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        upSeg(i);
    }
}

void prepare(){
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=n;i++){
        fa[i]=pa[i];
        mostl[i]=i;
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        x=pa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

void up(int x) {
    mostl[x] = ls[x] == 0 ? x : mostl[ls[x]];
}

bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

void rotate(int x) {
    int f = fa[x], g = fa[f];
    if (lr(x) == 0) {
        ls[f] = rs[x];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[x] = f;
    } else {
        rs[f] = ls[x];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[x] = f;
    }
    if (!isroot(f)) {
        if (lr(f) == 0) {
            ls[g] = x;
        } else {
            rs[g] = x;
        }
    }
    fa[f] = x;
    fa[x] = g;
    up(f);
    up(x);
}

void splay(int x) {
    while (!isroot(x)) {
        int f = fa[x];
        if (!isroot(f)) {
            if (lr(x) == lr(f)) {
                rotate(f);
            } else {
                rotate(x);
            }
        }
        rotate(x);
    }
}

void lazy(int x,int v){
    maxval[x]+=v;
    addtag[x]+=v;
}

void down(int x){
    if(addtag[x]){
        lazy(x<<1,addtag[x]);
        lazy(x<<1|1,addtag[x]);
        addtag[x]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        upSeg(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return maxval[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void add(int x,int v){
    add(dfn[x],dfn[x]+sz[x]-1,v,1,n,1);
}

void access(int x){
    for(int y=0;x!=0;y=x,x=fa[x]){
        splay(x);
        if(rs[x]!=0){
            add(mostl[rs[x]],1);
        }
        if(y!=0){
            add(mostl[y],-1);
        }
        rs[x]=y;
        up(x);
    }
}

int pathQuery(int x,int y){
    int xylca=lca(x,y);
    int a=query(dfn[x],dfn[x],1,n,1);
    int b=query(dfn[y],dfn[y],1,n,1);
    int c=query(dfn[xylca],dfn[xylca],1,n,1);
    return a+b-c*2+1;
}

int subtreeQuery(int x){
    return query(dfn[x],dfn[x]+sz[x]-1,1,n,1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x;
        if(op==1){
            access(x);
        }
        else if(op==2){
            cin>>y;
            cout<<pathQuery(x,y)<<endl;
        }
        else{
            cout<<subtreeQuery(x)<<endl;
        }
    }
    return 0;
}
