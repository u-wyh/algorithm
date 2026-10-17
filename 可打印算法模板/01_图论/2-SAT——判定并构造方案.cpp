// 用途：处理“两个条件至少满足一个”的布尔约束，并输出一组可行赋值。
// 时间：O(n+m)；空间：O(n+m)。
// 注意：点 x 表示 x=1，点 x+n 表示 x=0；数据量大，用定长数组模拟 DFS 栈。
// 例题：https://www.luogu.com.cn/problem/P4782
// 原代码：P4782.cpp；百万变量上限需要把递归 DFS 改成显式栈。
// 题意：每条限制为 (x1=v1) 或 (x2=v2)；无解输出 IMPOSSIBLE，否则输出任意方案。
// 思路：A 或 B 等价于 非A→B、非B→A；真假处于同一强连通分量则矛盾。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
const int MAXV = MAXN * 2;
const int MAXE = 2000000 + 5;
int n, m;
int head[MAXV], nxt[MAXE], to[MAXE], edgeCnt;
int dfn[MAXV], low[MAXV], belong[MAXV], timer, sccCnt;
int sccStack[MAXV], sccTop;

struct Frame { int u, edge, parent; };
Frame callStack[MAXV];

int node(int x, int value) { return value ? x : x + n; }
int opposite(int u) { return u <= n ? u + n : u - n; }

void addEdge(int u, int v) {
    to[++edgeCnt] = v;
    nxt[edgeCnt] = head[u];
    head[u] = edgeCnt;
}

void tarjan(int root) {
    int sp = 1;
    dfn[root] = low[root] = ++timer;
    sccStack[++sccTop] = root;
    callStack[sp] = {root, head[root], 0};
    while (sp) {
        Frame &frame = callStack[sp];
        int u = frame.u;
        if (frame.edge) {
            int e = frame.edge;
            frame.edge = nxt[e];
            int v = to[e];
            if (!dfn[v]) {
                dfn[v] = low[v] = ++timer;
                sccStack[++sccTop] = v;
                callStack[++sp] = {v, head[v], u};
            } else if (!belong[v]) { // 只用当前仍在 Tarjan 栈内的点更新 low。
                low[u] = min(low[u], dfn[v]);
            }
        } else {
            if (low[u] == dfn[u]) {
                ++sccCnt;
                int v;
                do {
                    v = sccStack[sccTop--];
                    belong[v] = sccCnt;
                } while (v != u);
            }
            int parent = frame.parent;
            --sp;
            if (parent) low[parent] = min(low[parent], low[u]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x1, v1, x2, v2; i <= m; ++i) {
        cin >> x1 >> v1 >> x2 >> v2;
        int a = node(x1, v1), b = node(x2, v2);
        addEdge(opposite(a), b);
        addEdge(opposite(b), a);
    }
    for (int u = 1; u <= 2 * n; ++u) {
        if (!dfn[u]) tarjan(u);
    }
    for (int x = 1; x <= n; ++x) {
        if (belong[x] == belong[x+n]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    cout << "POSSIBLE\n";
    // Tarjan 先弹出 DAG 下游分量，编号较小者优先取真。
    for (int x = 1; x <= n; ++x) {
        cout << (belong[x] < belong[x+n] ? 1 : 0) << (x == n ? '\n' : ' ');
    }
    return 0;
}
