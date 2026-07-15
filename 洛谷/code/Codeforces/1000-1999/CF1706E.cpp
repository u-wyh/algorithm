// 加边直到连通，C++版
// 图里有n个点，m条无向边，点的编号1~n，边的编号1~m，所有点都连通
// 一共有q条查询，每条查询格式如下
// 查询 l r : 至少要加完编号前多少的边，才能使得[l, r]中的所有点连通
// 1 <= n <= 10^5
// 1 <= m、q <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF1706E
// 测试链接 : https://codeforces.com/problemset/problem/1706/E
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题要将序号变为dfn序号
//如果要查询一个区间所有节点的lca  实际上就是这个区间dfn序号最小的和最大的两个点的lca
//我们可以构建一个stmin stmax倍增表查询区间dfn的最小和最大值
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXK = 200001;
const int MAXM = 200001;
const int MAXH = 20;

struct Edge {
    int u, v, w;
};

bool cmp(Edge x, Edge y) {
    return x.w < y.w;
}

int t, n, m, q;
Edge edge[MAXM];

// 并查集
int father[MAXK];

// Kruskal重构树
int head[MAXK];
int nxt[MAXK];
int to[MAXK];
int cntg;
int nodeKey[MAXK];
int cntu;

// 深度
int dep[MAXK];
// dfn序
int dfn[MAXK];
// seg[i] = j，代表树上节点的dfn序号为i，对应原始节点的编号为j
int seg[MAXK];
// 树上的倍增表
int stjump[MAXK][MAXH];
// dfn序号的计数
int cntd;

// 一维数组的倍增表，查询区间最大值、最小值
int lg2[MAXN];
int stmax[MAXN][MAXH];
int stmin[MAXN][MAXH];

void clear() {
    cntg = 0;
    cntd = 0;
    for (int i = 1; i <= n * 2; i++) {
        head[i] = 0;
    }
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void kruskalRebuild() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
    sort(edge + 1, edge + m + 1, cmp);
    cntu = n;
    for (int i = 1, fx, fy; i <= m; i++) {
        fx = find(edge[i].u);
        fy = find(edge[i].v);
        if (fx != fy) {
            father[fx] = father[fy] = ++cntu;
            father[cntu] = cntu;
            nodeKey[cntu] = edge[i].w;
            addEdge(cntu, fx);
            addEdge(cntu, fy);
        }
    }
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = ++cntd;
    seg[cntd] = u;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs(to[e], u);
    }
}

// 构建数组上的st表，讲解117进行了详细的讲述
void buildst() {
	lg2[0] = -1;
    for (int i = 1; i <= n; i++) {
    	lg2[i] = lg2[i >> 1] + 1;
        stmax[i][0] = dfn[i];
        stmin[i][0] = dfn[i];
    }
    for (int p = 1; p <= lg2[n]; p++) {
        for (int i = 1; i + (1 << p) - 1 <= n; i++) {
            stmax[i][p] = max(stmax[i][p - 1], stmax[i + (1 << (p - 1))][p - 1]);
            stmin[i][p] = min(stmin[i][p - 1], stmin[i + (1 << (p - 1))][p - 1]);
        }
    }
}

// 根据st表，[l..r]范围上的最小值，讲解117进行了详细的讲述
int dfnmin(int l, int r) {
    int p = lg2[r - l + 1];
    int ans = min(stmin[l][p], stmin[r - (1 << p) + 1][p]);
    return ans;
}

// 根据st表，[l..r]范围上的最大值，讲解117进行了详细的讲述
int dfnmax(int l, int r) {
    int p = lg2[r - l + 1];
    int ans = max(stmax[l][p], stmax[r - (1 << p) + 1][p]);
    return ans;
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (dep[stjump[a][p]] >= dep[b]) {
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

int query(int l, int r) {
    int x = seg[dfnmin(l, r)];
    int y = seg[dfnmax(l, r)];//变为对应的原始编号
    return nodeKey[lca(x, y)];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int test = 1; test <= t; test++) {
        cin >> n >> m >> q;
        for (int i = 1; i <= m; i++) {
            cin >> edge[i].u >> edge[i].v;
            edge[i].w = i;
        }
        clear();
        kruskalRebuild();
        dfs(cntu, 0);
        buildst();
        for (int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            if (l == r) {
                cout << 0 << " ";
            } else {
                cout << query(l, r) << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}