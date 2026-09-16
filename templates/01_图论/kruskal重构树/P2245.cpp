// Kruskal重构树模版题，C++版
// 图里有n个点，m条无向边，每条边给定边权，图里可能有若干个连通的部分
// 一共有q条查询，每条查询都是如下的格式
// 查询 x y : 点x和点y希望连通起来，其中的最大边权希望尽量小，打印这个值
//            如果怎样都无法联通，打印"impossible"
// 1 <= n <= 10^5
// 1 <= m <= 3 * 10^5
// 1 <= q <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P2245
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXK = 200001;//有1e5个原始节点  即叶节点 那么所有节点总数为至少两倍
const int MAXM = 300001;
const int MAXH = 20;

int n, m, q;

// 每条边有三个信息，节点u、节点v、边权w
struct Edge {
    int u, v, w;
};

bool cmp(Edge x, Edge y) {
    return x.w < y.w;
}

Edge edge[MAXM];

// 并查集
int father[MAXK];
// Kruskal重构树的建图
int head[MAXK];
int nxt[MAXK];
int to[MAXK];
int cntg;
// Kruskal重构树上，节点的权值
int nodeKey[MAXK];
// Kruskal重构树上，点的数量
int cntu;

// Kruskal重构树上，dfs过程建立的信息
int dep[MAXK];
int stjump[MAXK][MAXH];

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
    sort(edge + 1, edge + m + 1, cmp);//将边按照边权排序
    cntu = n;
    for (int i = 1; i <= m; i++) {
        int fx = find(edge[i].u);
        int fy = find(edge[i].v);
        if (fx != fy) {
            //如果这两个节点不是一个集合 那么合并  并将点权赋值为边权
            father[fx] = father[fy] = ++cntu;
            father[cntu] = cntu;
            nodeKey[cntu] = edge[i].w;
            addEdge(cntu, fx);
            addEdge(cntu, fy);
        }
    }
}

//建立倍增表信息
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs(to[e], u);
    }
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    kruskalRebuild();
    for (int i = 1; i <= cntu; i++) {
        if (i == father[i]) {
            //对于每棵树建立倍增表
            dfs(i, 0);
        }
    }
    cin >> q;
    for (int i = 1, x, y; i <= q; i++) {
        cin >> x >> y;
        if (find(x) != find(y)) {
            cout << "impossible" << "\n";
        } else {
            cout << nodeKey[lca(x, y)] << "\n";
        }
    }
    return 0;
}