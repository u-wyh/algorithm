#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MAXT = MAXN * 15;
int n, m, depth;

int head[MAXN];
int to[MAXN << 1];
int nxt[MAXN << 1];
int cntg = 0;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cntt = 0;

int dep[MAXN];
int siz[MAXN];
int dfn[MAXN];
int val[MAXN];
int cntd;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


void addedge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

int build(int l, int r) {
    int rt = ++cntt;
    sum[rt] = 0LL;
    if (l < r) {
        int mid = (l + r) >> 1;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

int add(int jobi, int jobv, int l, int r, int i) {
    int rt = ++cntt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    sum[rt] = sum[i] ^ jobv;
    if (l < r) {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            ls[rt] = add(jobi, jobv, l, mid, ls[rt]);
        } else {
            rs[rt] = add(jobi, jobv, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

//完成dfn序建立
void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    depth = max(depth, dep[u]);
    siz[u] = 1;
    dfn[u] = ++cntd;
    for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
        if (to[ei] != f) {
            dfs1(to[ei], u);
        }
    }
    for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
        if (to[ei] != f) {
            siz[u] += siz[to[ei]];
        }
    }
}

//在这个dfs中新建树
void dfs2(int u, int f) {
    root[dfn[u]] = add(dep[u], val[u] , 1, depth, root[dfn[u] - 1]);
    for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
        if (to[ei] != f) {
            dfs2(to[ei], u);
        }
    }
}

void prepare() {
    depth = 0;
    dfs1(1, 0);
    root[0] = build(1, depth);
    dfs2(1, 0);
}

int query(int jobl,int jobr,int l,int r,int u,int v){
    if(jobl<=l&&r<=jobr){
        return sum[v]^sum[u];
    }
    int ans=0;
    int mid=(l+r)/2;
    if(jobl<=mid){
        ans^=query(jobl,jobr,l,mid,ls[u],ls[v]);
    }
    if(jobr>mid){
        ans^=query(jobl,jobr,mid+1,r,rs[u],rs[v]);
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for (int i = 1, u, v; i < n; i++) {
        u=read();
        addedge(u,i+1);
        addedge(i+1,u);
    }
    prepare();
    for(int i = 1, a, k; i <= m; i++) {
        a=read(),k=read();
        cout << (double)query(dep[a],min(dep[a]+k,depth),1,depth,root[dfn[a] - 1], root[dfn[a] + siz[a] - 1])*1.0/1000.0 << endl;
    }
    return 0;
}

