// 删边和查询，C++版
// 图里有n个点，m条无向边，初始时点权都不同，图里可能有若干个连通的部分
// 一共有q条操作，每条操作是如下两种类型中的一种
// 操作 1 x : 点x所在的连通区域中，假设点y拥有最大的点权
//            打印y的点权，然后把y的点权修改为0
// 操作 2 x : 删掉第x条边
// 1 <= n <= 2 * 10^5    1 <= m <= 3 * 10^5    1 <= q <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF1416D
// 测试链接 : https://codeforces.com/problemset/problem/1416/D
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题线段树只是一个工具 没有什么很重要的作用  关键还是kruskal重构树
// 这道题只会为叶节点赋予dfn序号  很巧妙
// 这样的话 线段树可以通过区间查询 和单点修改
// 这道题最特殊的地方是如何给边赋边权
// 从始至终都存在的边  从1开始赋边权
// 后删除的边接着上面的数字  先删除的边边权更大
// 这样的话每次删一条边 就会使得limit-1  方便查询
// 每个节点记录自己子树内最小的dfn编号和最大的dfn序号
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXK = 400001;
const int MAXM = 300001;
const int MAXQ = 500001;
const int MAXH = 20;

struct Edge {
    int u, v, w;
};

bool cmp(Edge x, Edge y) {
    return x.w < y.w;
}

int n, m, q;

// 节点值的数组，需要记录，线段树也要使用
int node[MAXN];
// 所有边的数组，逆序处理删除操作，设置每条边的权值
Edge edge[MAXM];
// 记录所有操作
int ques[MAXQ][2];

// 并查集
int father[MAXK];

// Kruskal重构树
int head[MAXK];
int nxt[MAXK];
int to[MAXK];
int cntg;
int nodeKey[MAXK];
int cntu;

// 倍增表
int stjump[MAXK][MAXH];
// 子树上的叶节点个数
int leafsiz[MAXK];
// 子树上叶节点的dfn序号最小值
int leafDfnMin[MAXK];
// leafseg[i] = j，表示dfn序号为i的叶节点，原始编号为j
int leafseg[MAXK];
// dfn的计数
int cntd;

// 线段树的下标是dfn序号，维护范围内，拥有最大点权的dfn序号
int maxValueDfn[MAXN << 2];

//将所有的边赋上边权
void prepare() {
    for (int i = 1; i <= q; i++) {
        if (ques[i][0] == 2) {
            edge[ques[i][1]].w = -1;
        }
    }
    int weight = 0;
    for (int i = 1; i <= m; i++) {
        if (edge[i].w != -1) {
            edge[i].w = ++weight;
        }
    }
    for (int i = q; i >= 1; i--) {
        if (ques[i][0] == 2) {
            edge[ques[i][1]].w = ++weight;
        }
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
    for (int i = 1; i <= m; i++) {
        int fx = find(edge[i].u);
        int fy = find(edge[i].v);
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
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs(to[e], u);
    }
    if (u <= n) {
        leafsiz[u] = 1;
        leafDfnMin[u] = ++cntd;
        leafseg[cntd] = u;
    } else {
        leafsiz[u] = 0;
        leafDfnMin[u] = n + 1;
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        leafsiz[u] += leafsiz[to[e]];
        leafDfnMin[u] = min(leafDfnMin[u], leafDfnMin[to[e]]);
    }
}

int getAncestor(int u, int limit) {
    for (int p = MAXH - 1; p >= 0; p--) {
        if (stjump[u][p] > 0 && nodeKey[stjump[u][p]] <= limit) {
            u = stjump[u][p];
        }
    }
    return u;
}

void up(int i) {
    int l = i << 1;
    int r = i << 1 | 1;
    if (node[leafseg[maxValueDfn[l]]] > node[leafseg[maxValueDfn[r]]]) {
        maxValueDfn[i] = maxValueDfn[l];
    } else {
        maxValueDfn[i] = maxValueDfn[r];
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        maxValueDfn[i] = l;
    } else {
        int mid = (l + r) / 2;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

// dfn序号为jobi，点权更新成jobv
void update(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        node[leafseg[jobi]] = jobv;
    } else {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            update(jobi, jobv, l, mid, i << 1);
        } else {
            update(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// dfn范围[jobl..jobr]，哪个节点拥有最大点权，返回该节点的dfn序号
int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return maxValueDfn[i];
    } else {
        int mid = (l + r) / 2;
        int ldfn = 0, rdfn = 0;
        if (jobl <= mid) {
        	ldfn = query(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
        	rdfn = query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        if (node[leafseg[ldfn]] > node[leafseg[rdfn]]) {
            return ldfn;
        } else {
            return rdfn;
        }
    }
}

int queryAndUpdate(int x, int limit) {
    int anc = getAncestor(x, limit);
    int dfn = query(leafDfnMin[anc], leafDfnMin[anc] + leafsiz[anc] - 1, 1, n, 1);
    int ans = node[leafseg[dfn]];
    update(dfn, 0, 1, n, 1);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> node[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v;
        edge[i].w = 0;
    }
    for (int i = 1; i <= q; i++) {
        cin >> ques[i][0] >> ques[i][1];
    }
    prepare();
    kruskalRebuild();
    for (int i = 1; i <= cntu; i++) {
        if (i == father[i]) {
            dfs(i, 0);
        }
    }
    build(1, n, 1);
    int limit = m;
    for (int i = 1; i <= q; i++) {
        if (ques[i][0] == 1) {
            cout << queryAndUpdate(ques[i][1], limit) << "\n";
        } else {
            limit--;
        }
    }
    return 0;
}