#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int INF = INT_MAX;

int n,m;

struct Edge{
    int u,v,w;
    bool flag;
};
Edge edge[MAXN];

int fakruskal[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];
int sz[MAXN];
int faMST[MAXN];
int faweight[MAXN];
int dep[MAXN];

int faECC[MAXN];
int top[MAXN];
int minn[MAXN];

bool reach[MAXN];

int segf[MAXN<<2];
int lazyf[MAXN<<2];
int segans[MAXN<<2];
int lazyans[MAXN<<2];

bool cmp(Edge &a,Edge &b){
    return a.w<b.w;
}

int find(int x){
    return x==fakruskal[x]?x:fakruskal[x]=find(fakruskal[x]);
}

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void kruskal(){
    sort(edge+1,edge+m+1,cmp);
    for(int i=1;i<=n;i++){
        fakruskal[i]=i;
    }

    for(int i=1;i<=m;i++){
        int x=edge[i].u;
        int y=edge[i].v;
        int w=edge[i].w;
        int fx=find(x);
        int fy=find(y);
        if(fx!=fy){
            addedge(x,y,w);
            addedge(y,x,w);
            fakruskal[fx]=fy;
            edge[i].flag=true;
        }
    }
}

void dfs(int u,int f){
    faMST[u]=f;
    dfn[u]=++dfncnt;
    sz[u]=1;
    dep[u]=dep[f]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            faweight[v]=w;
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

int findECC(int x){
    return faECC[x]==x?x:faECC[x]=findECC(faECC[x]);
}

void initECC(){
    for(int i=1;i<=n;i++){
        faECC[i]=i;
        top[i]=i;
        minn[i]=INF;
    }
}

void build(int l,int r,int i,int *seg,int *lazy){
    seg[i]=INF;
    lazy[i]=INF;

    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1,seg,lazy);
        build(mid+1,r,i<<1|1,seg,lazy);
    }
}

void lazy(int jobv,int i,int *seg,int *lzy){
    seg[i]=min(seg[i],jobv);
    lzy[i]=min(lzy[i],jobv);
}

void down(int i,int *seg,int *lzy){
    if(lzy[i]!=INF){
        lazy(lzy[i],i<<1,seg,lzy);
        lazy(lzy[i],i<<1|1,seg,lzy);
        lzy[i]=INF;
    }
}

// 区间取 min
void update(int jobl, int jobr, int jobv, int l, int r, int i, int *seg, int *lzy) {
    if (jobl <= l && r <= jobr) {
        lazy(jobv, i, seg, lzy);
        return;
    }

    down(i, seg, lzy);

    int mid = (l + r) >> 1;

    if (jobl <= mid) {
        update(jobl, jobr, jobv, l, mid, i << 1, seg, lzy);
    }

    if (jobr > mid) {
        update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1, seg, lzy);
    }

    seg[i] = min(seg[i << 1], seg[i << 1 | 1]);
}

// 单点强制赋值
void update(int pos, int jobv, int l, int r, int i, int *seg, int *lzy) {
    if (l == r) {
        seg[i] = jobv;
        lzy[i] = INF;
        return;
    }

    down(i, seg, lzy);

    int mid = (l + r) >> 1;

    if (pos <= mid) {
        update(pos, jobv, l, mid, i << 1, seg, lzy);
    } else {
        update(pos, jobv, mid + 1, r, i << 1 | 1, seg, lzy);
    }

    seg[i] = min(seg[i << 1], seg[i << 1 | 1]);
}

// 单点查询
int query(int pos, int l, int r, int i, int *seg, int *lzy) {
    if (l == r) {
        return seg[i];
    }

    down(i, seg, lzy);

    int mid = (l + r) >> 1;

    if (pos <= mid) {
        return query(pos, l, mid, i << 1, seg, lzy);
    } else {
        return query(pos, mid + 1, r, i << 1 | 1, seg, lzy);
    }
}

void markReach(int u, int curMax) {
    if (reach[u]) return;

    reach[u] = true;

    int f = query(dfn[u], 1, n, 1, segf, lazyf);

    // f 理论上一定不是 INF；保险起见判断一下
    if (f != INF) {
        update(dfn[u], f + curMax, 1, n, 1, segans, lazyans);
    }

    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];

        // 只往 MST 的儿子方向走
        if (faMST[v] != u) continue;

        // 当前最大边权 curMax 下，只能经过权值 <= curMax 的树边
        if (!reach[v] && weight[i] <= curMax) {
            markReach(v, curMax);
        }
    }
}

// 非树边形成环，合并 MST 上 u-v 路径
int mergePath(int u, int v, int w) {
    while (findECC(u) != findECC(v)) {
        int ru = findECC(u);
        int rv = findECC(v);

        int tu = top[ru];
        int tv = top[rv];

        // 每次合并深度更大的那个分量
        if (dep[tu] < dep[tv]) {
            swap(u, v);
            swap(ru, rv);
            swap(tu, tv);
        }

        int father = faMST[tu];
        int rf = findECC(father);

        // 当前分量向父亲分量合并
        // 新分量中的最小边权来自：
        // 1. 原 ru 分量内部 minn[ru]
        // 2. 父亲 rf 分量内部 minn[rf]
        // 3. tu 到父亲的 MST 树边 faweight[tu]
        // 4. 当前非树边 w
        minn[rf] = min(minn[rf], minn[ru]);
        minn[rf] = min(minn[rf], faweight[tu]);
        minn[rf] = min(minn[rf], w);

        faECC[ru] = rf;
    }

    int r = findECC(u);
    minn[r] = min(minn[r], w);

    return r;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edge[i]={u,v,w,false};
    }

    kruskal();

    faweight[1]=INF;
    dfs(1,0);

    initECC();

    build(1,n,1,segf,lazyf);
    build(1,n,1,segans,lazyans);

    reach[1] = true;

        for (int i = 1; i <= m; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;

        int ru = findECC(u);
        int rv = findECC(v);

        // 已经在同一个动态边双分量里，跳过
        if (ru == rv) continue;

        if (edge[i].flag) {
            // 树边：负责让新点可达
            int child;

            if (faMST[u] == v) {
                child = u;
            } else {
                child = v;
            }

            // 从 1 到 child 子树中的点都会经过这条树边
            update(dfn[child], dfn[child] + sz[child] - 1, w, 1, n, 1, segf, lazyf);

            // 如果父亲已经可达，那么 child 子树中边权 <= w 的部分也会变得可达
            if (reach[faMST[child]] && !reach[child]) {
                markReach(child, w);
            }
        } else {
            // 非树边：负责形成环，压缩边双分量
            int r = mergePath(u, v, w);
            r = findECC(r);

            int t = top[r];
            int mn = minn[r];

            // 这个环/边双分量可以让最小边权变成 mn
            update(dfn[t], dfn[t] + sz[t] - 1, mn, 1, n, 1, segf, lazyf);

            // 当前最大边权是 w，所以答案候选是 mn + w
            if (mn != INF) {
                update(dfn[t], dfn[t] + sz[t] - 1, mn + w, 1, n, 1, segans, lazyans);
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        cout << query(dfn[i], 1, n, 1, segans, lazyans) << '\n';
    }
    return 0;
}