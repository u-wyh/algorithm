#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const long long INF = 1e12;

int n,m;
int arr[MAXN];

long long mincost[MAXN];
int from[MAXN];
long long minval[MAXN];
long long cost[MAXN];
long long val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int fa[MAXN];
int dep[MAXN];
int siz[MAXN];//子树大小
int son[MAXN];//重儿子节点编号
int top[MAXN];//所在重链头节点
int dfn[MAXN];//dfn序号
int seg[MAXN];//dfn序号对应的原始节点编号
int cntd = 0;

long long sum[MAXN<<2];
int tree[MAXN<<2];

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

void dfs(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
    mincost[u]=0,from[u]=u,minval[u]=arr[u];
    cost[u]=INF,val[u]=-INF;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v==fa){
            continue;
        }
        if((w+mincost[v]<mincost[u])||(mincost[u]==(mincost[v]+w)&&(minval[u]<minval[v]+arr[u]))){
            cost[u]=mincost[u],val[u]=minval[u];
            mincost[u]=mincost[v]+w,minval[u]=minval[v]+arr[u],from[u]=v;
        }
        else if((w+mincost[v]<cost[u])||(cost[u]==(mincost[v]+w)&&(val[u]<minval[v]+arr[u]))){
            cost[u]=w+mincost[v],val[u]=minval[v]+arr[u];
        }
    }
}

void dfs1(int u,int fa,int w){
    if(fa!=0){
        if(from[fa]==u){
            if((cost[fa]+w)<mincost[u]||((cost[fa]+w)==mincost[u]&&(val[fa]+arr[u]>minval[u]))){
                cost[u]=mincost[u],val[u]=minval[u];
                mincost[u]=cost[fa]+w,minval[u]=val[fa]+arr[u],from[u]=fa;
            }
            else if((cost[fa]+w)<cost[u]||((cost[fa]+w)==cost[u]&&(val[fa]+arr[u]>val[u]))){
                cost[u]=cost[fa]+w,val[u]=val[fa]+arr[u];
            }
        }
        else{
            if((mincost[fa]+w)<mincost[u]||((mincost[fa]+w)==mincost[u]&&(minval[fa]+arr[u]>minval[u]))){
                cost[u]=mincost[u],val[u]=minval[u];
                mincost[u]=mincost[fa]+w,minval[u]=minval[fa]+arr[u],from[u]=fa;
            }
            else if((mincost[fa]+w)<cost[u]||((mincost[fa]+w)==cost[u]&&(minval[fa]+arr[u]>val[u]))){
                cost[u]=mincost[fa]+w,val[u]=minval[fa]+arr[u];
            }
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa){
            dfs1(v,u,w);
        }
    }
}

void dfs2(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dfs2(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            siz[u] += siz[v];
            if (son[u] == 0 || siz[son[u]] < siz[v]) {
                son[u] = v;
            }
        }
    }
}

void dfs3(int u, int t) {
    top[u] = t;
    dfn[u] = ++cntd;
    seg[cntd] = u;
    if (son[u] == 0) {
        return;
    }
    dfs3(son[u], t);//去 重儿子继续向下
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            //轻儿子自己开一条重链 自己做头结点
            dfs3(v, v);
        }
    }
}

inline int fun(int u,int v){
    if(u==0||v==0){
        return u+v;
    }
    int ans=0;
    if(mincost[u]<mincost[v]||(mincost[u]==mincost[v]&&minval[u]>minval[v])){
        ans=u;
    }
    else{
        ans=v;
    }
    return ans;
}

void up(int i) {
    sum[i] = (sum[i << 1] + sum[i << 1 | 1]) ;
    tree[i]=fun(tree[i<<1],tree[i<<1|1]);
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[seg[l]];
        tree[i]=seg[l];
        // cout<<l<<' '<<seg[l]<<' '<<sum[i]<<endl;
    } else {
        int mid = (l + r) / 2;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

long long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) / 2;
    long long ans = 0;
    if (jobl <= mid) {
        ans = (ans + query(jobl, jobr, l, mid, i << 1)) ;
    }
    if (jobr > mid) {
        ans = (ans + query(jobl, jobr, mid + 1, r, i << 1 | 1)) ;
    }
    return ans;
}

int querymin(int jobl,int jobr,int l,int r,int i){
    if (jobl <= l && r <= jobr) {
        return tree[i];
    }
    int mid = (l + r) / 2;
    if (jobl <= mid&&jobr>mid) {
        return fun(querymin(jobl, jobr, l, mid, i << 1),querymin(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    else if(jobl<=mid){
        return querymin(jobl, jobr, l, mid, i << 1);
    }
    else {
        return querymin(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
}

long long pathquery(int x,int y){
    long long ans=0;
    int res=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            swap(x,y);
        }
        ans+=query(dfn[top[x]],dfn[x],1,n,1);
        res=fun(res,querymin(dfn[top[x]],dfn[x],1,n,1));
        x=fa[top[x]];
    }
    ans+=query(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1);
    res=fun(res,querymin(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1));
    // cout<<ans<<' '<<minval[res]<<' ';
    return ans+minval[res];
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs(1,0);
    dfs1(1,0,0);
    for(int u=1;u<=n;u++){
        minval[u]=minval[u]*2-arr[u];
    }
    dfs2(1,0);
    dfs3(1,1);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        printf("%lld\n",pathquery(u,v));
    }
    return 0;
}