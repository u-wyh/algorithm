// 用途：一般连通无向图建圆方树，查询两点之间所有路径都必经的原图顶点数。
// 建树 O(n+m+nlogn)，单次查询 O(logn)；空间 O(nlogn+m)。
// 注意：重边按边编号跳过父边；自环不影响本题答案；大图用定长数组模拟 DFS 栈。
// 例题：https://www.luogu.com.cn/problem/P4320
// 原代码：P4320.cpp；50 万点上限需要把递归 DFS 改成显式栈。
// 题意：询问 x 到 y 无论走哪条路都要经过几个点，x、y 本身也算。
// 思路：每个点双建一个方点，连向其中的原图圆点；圆方树路径上的圆点都是必经点。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000 + 5;
const int MAXM = 1000000 + 5;
const int MAXV = MAXN * 2;
const int MAXGE = MAXM * 2;
const int MAXTE = MAXN * 4;
const int LOG = 21;
int n, m, q, nodeCnt;
int head1[MAXN], next1[MAXGE], to1[MAXGE], cnt1 = 1;
int head2[MAXV], next2[MAXTE], to2[MAXTE], cnt2;
int dfn[MAXN], low[MAXN], timer;
int vertexStack[MAXN], vertexTop;
int depth[MAXV], up[MAXV][LOG], que[MAXV];

struct Frame { int u, edge, parentEdge; };
Frame callStack[MAXN];

void addEdge1(int u, int v) {
    to1[++cnt1] = v;
    next1[cnt1] = head1[u];
    head1[u] = cnt1;
}

void addEdge2(int u, int v) {
    to2[++cnt2] = v;
    next2[cnt2] = head2[u];
    head2[u] = cnt2;
}

void linkTree(int u, int v) {
    addEdge2(u, v);
    addEdge2(v, u);
}

void tarjan(int root) {
    int sp = 1;
    dfn[root] = low[root] = ++timer;
    vertexStack[++vertexTop] = root;
    callStack[sp] = {root, head1[root], 0};
    while (sp) {
        Frame &frame = callStack[sp];
        int u = frame.u;
        if (frame.edge) {
            int e = frame.edge;
            frame.edge = next1[e];
            if ((e ^ 1) == frame.parentEdge) continue;
            int v = to1[e];
            if (!dfn[v]) {
                dfn[v] = low[v] = ++timer;
                vertexStack[++vertexTop] = v;
                callStack[++sp] = {v, head1[v], e};
            } else if (dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
            }
        } else {
            int parentEdge = frame.parentEdge;
            --sp;
            if (parentEdge) {
                int parent = to1[parentEdge ^ 1];
                low[parent] = min(low[parent], low[u]);
                if (low[u] >= dfn[parent]) {
                    int square = ++nodeCnt; // 一个点双对应一个新方点。
                    linkTree(square, parent);
                    int v;
                    do {
                        v = vertexStack[vertexTop--];
                        linkTree(square, v);
                    } while (v != u);
                }
            } else {
                --vertexTop; // 根圆点不属于后续连通块的 DFS 栈。
            }
        }
    }
}

void buildLca() {
    int left = 1, right = 0;
    que[++right] = 1;
    depth[1] = 1;
    while (left <= right) {
        int u = que[left++];
        for (int e = head2[u]; e; e = next2[e]) {
            int v = to2[e];
            if (v == up[u][0]) continue;
            up[v][0] = u;
            depth[v] = depth[u] + 1;
            for (int k = 1; k < LOG; ++k) {
                up[v][k] = up[up[v][k-1]][k-1];
            }
            que[++right] = v;
        }
    }
}

int lca(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    for (int k = LOG-1; k >= 0; --k) {
        if (depth[up[x][k]] >= depth[y]) x = up[x][k];
    }
    if (x == y) return x;
    for (int k = LOG-1; k >= 0; --k) {
        if (up[x][k] != up[y][k]) {
            x = up[x][k];
            y = up[y][k];
        }
    }
    return up[x][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    nodeCnt = n;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        if (u == v) continue; // 自环不改变任意两点间的必经顶点。
        addEdge1(u, v);
        addEdge1(v, u);
    }
    tarjan(1); // 例题保证原图连通。
    buildLca();
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        int z = lca(x, y);
        // 圆点与方点交替；两个原图顶点间的路径长度一定为偶数。
        cout << (depth[x] + depth[y] - 2 * depth[z]) / 2 + 1 << '\n';
    }
    return 0;
}
