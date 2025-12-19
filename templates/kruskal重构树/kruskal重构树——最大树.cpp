// youyou的军训，C++版
// 图里有n个点，m条无向边，每条边给定不同的边权，图里可能有若干个连通的部分
// 一共有q条操作，每条操作都是如下的三种类型中的一种
// 操作 1 x   : 限制变量limit，把limit的值改成x
// 操作 2 x   : 点x不能走过任何边权小于limit的边，打印此时x所在的连通区域大小
// 操作 3 x y : 第x条边的边权修改为y，题目保证修改之后，第x条边的边权排名不变
// 1 <= n、m、q <= 4 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P9638
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题是先建立一棵树  然后从顶点向下寻找合适的节点  从而求出答案
#include <bits/stdc++.h>
using namespace std;
const int MAXK = 800001;
const int MAXM = 400001;
const int MAXH = 20;

int n, m, q;

struct Edge {
    int u, v, w, i;
};

bool cmp(Edge x, Edge y) {
    return x.w > y.w;
}
// 每条边的信息，节点u、节点v、边权w、边的编号i
Edge edge[MAXM];
// 边的编号对应重构树上的点的编号  为了方便操作3
int edgeToTree[MAXM];

// 并查集
int father[MAXK];

// Kruskal重构树
int head[MAXK];
int nxt[MAXK];
int to[MAXK];
int cntg;
int nodeKey[MAXK];
int cntu;

// 树上dfs，Kruskal重构树的节点，子树上面有几个叶节点  为了统计操作2的答案
int leafsiz[MAXK];
// 树上dfs，Kruskal重构树的节点，倍增表
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
    sort(edge + 1, edge + m + 1, cmp);//这道题目要求实际上是将边按照从大到小排序
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
            edgeToTree[edge[i].i] = cntu;//比较特殊的是要记录这个节点是那条边转换来的
        }
    }
}

void dfs(int u, int fa) {
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs(to[e], u);
    }
    if (u <= n) {
        //说明本来就是图上的点  即叶节点
        leafsiz[u] = 1;
    } else {
        leafsiz[u] = 0;
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        leafsiz[u] += leafsiz[to[e]];//统计以u为首的子树上一共有多少叶节点
    }
}

//查询u节点所在联通区域  限制为limit的可以到达的节点总数
int query(int u, int limit) {
    for (int p = MAXH - 1; p >= 0; p--) {
        if (stjump[u][p] > 0 && nodeKey[stjump[u][p]] >= limit) {
            //首先  肯定是越往上越好 但是前提是必须有这个祖先存在
            //即使这个祖先存在  这个节点的权值也必须大于limit才行
            u = stjump[u][p];
        }
    }
    return leafsiz[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        edge[i].i = i;
    }
    kruskalRebuild();
    for (int i = 1; i <= cntu; i++) {
        if (i == father[i]) {
            dfs(i, 0);
        }
    }
    int op, x, y, limit = 0;
    for (int i = 1; i <= q; i++) {
        cin >> op;
        if (op == 1) {
            cin >> limit;
        } else if (op == 2) {
            cin >> x;
            cout << query(x, limit) << "\n";
        } else {
            cin >> x >> y;
            if (edgeToTree[x] != 0) {
                nodeKey[edgeToTree[x]] = y;
            }
        }
    }
    return 0;
}