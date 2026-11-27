// https://www.luogu.com.cn/problem/P3976
// 题意：第一行输入城市数 n，第二行输入 n 座城市宝石初始价格 p，接下来 n-1 行每行输入一条树边 (x, y)；
// 再输入询问数 q，接下来 q 行输入 a, b, v。
// 每次询问 ZJY 从 a 走到 b 的树上简单路径，在路径上先选一城市买入宝石再到之后（或同城）卖出的最大利润（亏本则为 0）；
// 询问结束后，该路径上所有城市的宝石价格均上涨 v。
// 对每次询问输出一行最大利润。
// 数据范围：对于 100% 的数据，1 <= n, q <= 5 * 10^4，初始价格不超过 100，任意时刻任何城市宝石价格不超过 10^9。
#include<bits/stdc++.h>
// 算法标签：树链剖分、线段树
using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9+1;

int n,m;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int dep[MAXN];
int sz[MAXN];
int top[MAXN];
int fa[MAXN];
int son[MAXN];

int maxv[MAXN<<2];
int minv[MAXN<<2];
int lprofit[MAXN<<2];
int rprofit[MAXN<<2];
int tag[MAXN<<2];

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[son[u]]<sz[v]){
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

void up(int i){
    maxv[i]=max(maxv[i<<1],maxv[i<<1|1]);
    minv[i]=min(minv[i<<1],minv[i<<1|1]);
    lprofit[i]=max(max(lprofit[i<<1],lprofit[i<<1|1]),maxv[i<<1|1]-minv[i<<1]);
    rprofit[i]=max(max(rprofit[i<<1],rprofit[i<<1|1]),maxv[i<<1]-minv[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        maxv[i]=minv[i]=val[seg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    maxv[i]+=v;
    minv[i]+=v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
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

void merge(int ans[], int *b) {
    int lmax  = ans[0];
    int lmin  = ans[1];
    int llpro = ans[2];
    int lrpro = ans[3];
    ans[0] = max(lmax, b[0]);
    ans[1] = min(lmin, b[1]);
    ans[2] = max({llpro, b[2], b[0] - lmin});
    ans[3] = max({lrpro, b[3], lmax - b[1]});
    //和up函数的信息组合方式一样
}

void query(int ans[], int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        int tmp[4]={maxv[i], minv[i], lprofit[i], rprofit[i]};
        //将以前收集的信息和目前的信息合并  以前的信息肯定是左侧部分的信息
        merge(ans, tmp);
    } else {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            query(ans, jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            query(ans, jobl, jobr, mid + 1, r, i << 1 | 1);
        }
    }
}

// ans[0] : 线段树更左侧部分的max
// ans[1] : 线段树更左侧部分的min
// ans[2] : 线段树更左侧部分的lprofit
// ans[3] : 线段树更左侧部分的rprofit
// 随着线段树查询的展开，会有更右部分的信息整合进ans，最终整合出整体信息
void query(int ans[], int jobl, int jobr) {
    ans[0] = -INF;
    ans[1] =  INF;
    ans[2] =  0;
    ans[3] =  0;
    //初始时将ans数组  最大值设置为较小值  最小值设置为较大值  左右利润都设置为0  方便后来覆盖
    query(ans, jobl, jobr, 1, n, 1);
}

void clone(int *a,int *b){
    a[0]=b[0];
    a[1]=b[1];
    a[2]=b[2];
    a[3]=b[3];
}

int pathquery(int x,int y){
    int xpath[4]={-INF,INF,0,0};
    int ypath[4]={-INF,INF,0,0};
    int cur[4];

    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            query(cur,dfn[top[x]],dfn[x]);
            merge(cur,xpath);
            clone(xpath,cur);
            x=fa[top[x]];
        }
        else{
            query(cur,dfn[top[y]],dfn[y]);
            merge(cur,ypath);
            clone(ypath,cur);
            y=fa[top[y]];
        }
    }
    if(dep[x]<=dep[y]){
        query(cur,dfn[x],dfn[y]);
        merge(cur,xpath);
        clone(xpath,cur);
    }
    else{
        query(cur,dfn[y],dfn[x]);
        merge(cur,ypath);
        clone(ypath,cur);
    }
    return max(max(xpath[3],ypath[2]),ypath[0]-xpath[1]);
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

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);

    cin>>m;
    for(int i=1;i<=m;i++){
        int x,y,v;
        cin>>x>>y>>v;
        cout<<pathquery(x,y)<<endl;
        pathadd(x,y,v);
    }
    return 0;
}