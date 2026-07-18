#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;
const int MAXV = 300000 + 5;
const int LOG = 20;

// 记录原图中的道路
struct Edge {
    int u, v, w;
};

// 城市数、道路数
int n, m;

// 重构树节点总数和根节点
int tot, root;

// 按边权排序后的道路
Edge edge[MAXM];

// 并查集父节点
int dsu[MAXN];

// 并查集大小
int dsuSize[MAXN];

// 每个并查集当前对应的重构树节点
int comp[MAXN];

// 当前已加入道路中每个城市的度数
int degreev[MAXN];

// 重构树父节点
int fa[MAXV];

// 重构树深度
int dep[MAXV];

// 重构树节点对应的边权
int val[MAXV];

// 倍增祖先
int up[MAXV][LOG];

// 当前连通块是否已经可以交换
bool good[MAXV];

// 按照边权排序
bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

// 查找并查集根节点
int find(int x) {
    if (dsu[x] == x) {
        return x;
    }

    dsu[x] = find(dsu[x]);
    return dsu[x];
}

// 建立 Kruskal 重构树
void buildReconstructionTree() {
    sort(edge + 1, edge + m + 1, cmp);

    for (int i = 1; i <= m; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;

        degreev[u]++;
        degreev[v]++;

        int a = find(u);
        int b = find(v);

        tot++;
        val[tot] = w;

        // 在同一个连通块中加入边，一定产生环
        if (a == b) {
            fa[comp[a]] = tot;
            good[tot] = true;
            comp[a] = tot;
            continue;
        }

        // 新节点成为两个旧连通块节点的父亲
        fa[comp[a]] = tot;
        fa[comp[b]] = tot;

        // 继承原连通块的可交换性质
        good[tot] = good[comp[a]] || good[comp[b]];

        // 当前边可能让端点度数达到 3
        if (degreev[u] >= 3 || degreev[v] >= 3) {
            good[tot] = true;
        }

        // 按大小合并并查集
        if (dsuSize[a] < dsuSize[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }

        dsu[b] = a;
        dsuSize[a] += dsuSize[b];
        comp[a] = tot;
    }

    root = comp[find(1)];
}

// 预处理深度和倍增祖先
void buildLca() {
    dep[root] = 1;

    // 重构树中父节点编号一定大于子节点编号
    for (int i = tot; i >= 1; i--) {
        if (i != root) {
            dep[i] = dep[fa[i]] + 1;
        }

        up[i][0] = fa[i];

        for (int j = 1; j < LOG; j++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
}

// 求两个节点的最近公共祖先
int lca(int x, int y) {
    if (dep[x] < dep[y]) {
        int tmp = x;
        x = y;
        y = tmp;
    }

    int d = dep[x] - dep[y];

    for (int i = LOG - 1; i >= 0; i--) {
        if (d & (1 << i)) {
            x = up[x][i];
        }
    }

    if (x == y) {
        return x;
    }

    for (int i = LOG - 1; i >= 0; i--) {
        if (up[x][i] != up[y][i]) {
            x = up[x][i];
            y = up[y][i];
        }
    }

    return up[x][0];
}

// 找到最低的 good 祖先
int firstGoodAncestor(int x) {
    if (good[x]) {
        return x;
    }

    // 尽可能向上跳，但仍停留在非 good 节点
    for (int i = LOG - 1; i >= 0; i--) {
        int a = up[x][i];

        if (a && !good[a]) {
            x = a;
        }
    }

    return up[x][0];
}

// 初始化
void init(
    int N,
    int M,
    vector<int> U,
    vector<int> V,
    vector<int> W
) {
    n = N;
    m = M;
    tot = n;

    // 原城市编号整体加一，保留 0 作为空节点
    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        dsuSize[i] = 1;
        comp[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        edge[i].u = U[i - 1] + 1;
        edge[i].v = V[i - 1] + 1;
        edge[i].w = W[i - 1];
    }

    buildReconstructionTree();
    buildLca();
}

// 回答一次询问
int getMinimumFuelCapacity(int X, int Y) {
    int x = X + 1;
    int y = Y + 1;

    // X、Y 第一次连通时对应的连通块状态
    int p = lca(x, y);

    // 找到第一个已经能够交换的状态
    p = firstGoodAncestor(p);

    if (p == 0) {
        return -1;
    }

    return val[p];
}