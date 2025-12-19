#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*50;
const int MAXV = 1e5;
const int MAXH = 22;

int n,m,p;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dep[MAXN];
int st[MAXN][MAXH];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int maxcnt[MAXT];
int cntv;

int ans[MAXN];

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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

inline int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=p;i>=0;i--){
        if(dep[st[x][i]]>=dep[y]){
            x=st[x][i];
        }
    }
    if(x==y) return x;
    for(int i=p;i>=0;i--){
        if(st[x][i]!=st[y][i]){
            x=st[x][i];
            y=st[y][i];
        }
    }
    return st[x][0];
}

void up(int i){
    maxcnt[i]=max(maxcnt[ls[i]],maxcnt[rs[i]]);
}

int add(int pos,int jobv,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntv;
    }
    if(l==r){
        maxcnt[rt]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=add(pos,jobv,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(pos,jobv,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l, int r, int t1, int t2) {
    if (t1 == 0 || t2 == 0) {
        return t1 + t2;
    }
    if (l == r) {
        // 遇到叶子结点
        maxcnt[t1] += maxcnt[t2];
    } else {
        int mid = (l + r) >> 1;
        ls[t1] = merge(l, mid, ls[t1], ls[t2]);
        rs[t1] = merge(mid + 1, r, rs[t1], rs[t2]);
        up(t1);
    }
    return t1;
}

int query(int l,int r,int i){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        if(maxcnt[ls[i]]>=maxcnt[rs[i]]){
            return query(l,mid,ls[i]);
        }
        else{
            return query(mid+1,r,rs[i]);
        }
    }
}

void dfs1(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            root[u]=merge(1,MAXV,root[u],root[v]);
        }
    }
    if(maxcnt[root[u]]==0){
        ans[u]=0;
    }
    else{
        ans[u]=query(1,MAXV,root[u]);
    }
}

int main()
{
    n=read(),m=read();
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int x,y,v;
        x=read(),y=read(),v=read();
        int xylca=lca(x,y);
        int falca=st[xylca][0];
        root[x]=add(v,1,1,MAXV,root[x]);
        root[y]=add(v,1,1,MAXV,root[y]);
        root[xylca]=add(v,-1,1,MAXV,root[xylca]);
        root[falca]=add(v,-1,1,MAXV,root[falca]);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}