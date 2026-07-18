// 网络，C++版
// 一共有n个服务器，给定n-1条边，所有服务器连成一棵树
// 某两个服务器之间的路径上，可能接受一条请求，路径上的所有服务器都需要保存该请求的重要度
// 一共有m条操作，每条操作是如下3种类型中的一种，操作依次发生，第i条操作发生的时间为i
// 操作 0 x y v : x号服务器到y号服务器的路径上，增加了一个重要度为v的请求
// 操作 1 t     : 当初时间为t的操作，一定是增加请求的操作，现在这个请求结束了
// 操作 2 x     : 当前时间下，和x号服务器无关的所有请求中，打印最大的重要度
// 关于操作2，如果当前时间下，没有任何请求、或者所有请求都和x号服务器有关，打印-1
// 2 <= n <= 10^5    1 <= m <= 2 * 10^5    1 <= 重要度 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P3250
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题结合了很多的算法：树上点差分、dfn序、倍增求lca、树状数组、整体二分
//添加信息的时候只需要在 a b lca(a,b) lcafa上加减即可
//查询一个节点的信息时 需要在树状数组上查询区间和
//整体二分也是根据操作的重要度的权值进行的
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXM = 200001;
const int MAXH = 20;
const int INF = 1000000001;

int n, m;

// 链式前向星
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 0;

// 树上点差分 + 树上倍增
int fa[MAXN];
int dep[MAXN];
int siz[MAXN];
int dfn[MAXN];
int stjump[MAXN][MAXH];
int cntd = 0;

// 树状数组
int tree[MAXN];

// 事件编号组成的数组
int eid[MAXM];
// 如果op == 0，添加点x到点y，重要度为v的路径
// 如果op == 1，删除点x到点y，重要度为v的路径
// 如果op == 2，查询和x相关的答案，y表示问题的编号
int op[MAXM];
int x[MAXM];
int y[MAXM];
int v[MAXM];
int cntq = 0;

// 整体二分
int lset[MAXM];
int rset[MAXM];

int ans[MAXM];

//建树
void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

//建立倍增信息
void dfs(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    dfn[u] = ++cntd;
    stjump[u][0] = f;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e != 0; e = nxt[e]) {
        if (to[e] != f) {
            dfs(to[e], u);
        }
    }
    for (int e = head[u]; e != 0; e = nxt[e]) {
        if (to[e] != f) {
            siz[u] += siz[to[e]];
        }
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

int lowbit(int i) {
    return i & -i;
}

void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

int query(int i) {
    int ret = 0;
    while (i > 0) {
        ret += tree[i];
        i -= lowbit(i);
    }
    return ret;
}

// 点x到点y的路径上，每个点增加v个请求数量
void pathAdd(int x, int y, int v) {
    int xylca = lca(x, y);
    int lcafa = fa[xylca];
    add(dfn[x], v);
    add(dfn[y], v);
    add(dfn[xylca], -v);
    if (lcafa != 0) {
        add(dfn[lcafa], -v);
    }
}

// 查询和x点相关的请求数量
int pointQuery(int x) {
    return query(dfn[x] + siz[x] - 1) - query(dfn[x] - 1);
}

void compute(int el, int er, int vl, int vr) {
    if (el > er) {
        return;
    }
    if (vl == vr) {
        for (int i = el; i <= er; i++) {
            int id = eid[i];
            if (op[id] == 2) {
                ans[y[id]] = vl;
            }
        }
    } else {
        //这个地方是比较特殊的  先执行的是mid~r的操作
        //逻辑是：当执行某条指令之后  全局一共执行了request条操作
        //查询的时候 如果这个节点上的执行操作为a  那么肯定有a<=request  因为a一定不会超过request
        //如果a==request  那么说明在 mid~目前的指令 全都要经过这个节点  那么和这个节点无关的指令最大值要么不存在  要么在l~mid上
        //如果a<request  那么与这个节点无关的最大操作一定在右边
        int mid = (vl + vr) / 2;
        int lsiz = 0, rsiz = 0, request = 0;
        for (int i = el; i <= er; i++) {
            int id = eid[i];
            if (op[id] == 0) {
                if (v[id] <= mid) {
                    lset[++lsiz] = id;
                } else {
                    pathAdd(x[id], y[id], 1);
                    request++;
                    rset[++rsiz] = id;
                }
            } else if (op[id] == 1) {
                if (v[id] <= mid) {
                    lset[++lsiz] = id;
                } else {
                    pathAdd(x[id], y[id], -1);
                    request--;
                    rset[++rsiz] = id;
                }
            } else {
                if (pointQuery(x[id]) == request) {
                    lset[++lsiz] = id;
                } else {
                    rset[++rsiz] = id;
                }
            }
        }

        for (int i = 1; i <= lsiz; i++) {
            eid[el + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsiz; i++) {
            eid[el + lsiz + i - 1] = rset[i];
        }
        //复原操作
        for (int i = 1; i <= rsiz; i++) {
            int id = rset[i];
            if (op[id] == 0 && v[id] > mid) {
                pathAdd(x[id], y[id], -1);
            }
            if (op[id] == 1 && v[id] > mid) {
                pathAdd(x[id], y[id], 1);
            }
        }
        compute(el, el + lsiz - 1, vl, mid);
        compute(el + lsiz, er, mid + 1, vr);
    }
}

void prepare() {
    dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        if (op[i] == 1) {
            int pre = x[i];
            x[i] = x[pre];
            y[i] = y[pre];
            v[i] = v[pre];
        }
        if (op[i] == 2) {
            y[i] = ++cntq;
        }
    }
    for (int i = 1; i <= m; i++) {
        eid[i] = i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= m; i++) {
        cin >> op[i] >> x[i];
        if (op[i] == 0) {
            cin >> y[i] >> v[i];
        }
    }
    prepare();
    compute(1, m, 0, INF);
    for (int i = 1; i <= cntq; i++) {
        if (ans[i] == 0) {
            cout << -1 << '\n';
        } else {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}