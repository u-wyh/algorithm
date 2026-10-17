// 用途：树上大量已知的 LCA 查询一次性离线求解。
// 时间：O((n+q)α(n))；空间：O(n+q)。
// 注意：所有询问须先读入；百万点长链用定长数组模拟 DFS 栈。
// 例题：https://www.luogu.com.cn/problem/P3379
// 原代码：P3379.cpp；修复原图边数组容量，并改用定长显式栈处理长链。
// 题意：给定树根和多组点对，输出每对点的最近公共祖先。
// 思路：DFS 处理完子树后与父点并查集合并；两端都处理完时，另一端所在集合的祖先即 LCA。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
const int MAXE = MAXN * 2;
int n, q, root;
int head[MAXN], nxt[MAXE], to[MAXE], edgeCnt;
int queryHead[MAXN], queryNext[MAXE], queryTo[MAXE], queryId[MAXE], queryCnt;
int answer[MAXN];
int dsu[MAXN], dsuSize[MAXN], ancestor[MAXN];
bool finished[MAXN];

struct Frame { int u, parent, edge; };
Frame callStack[MAXN];

void addEdge(int u, int v) {
    to[++edgeCnt] = v;
    nxt[edgeCnt] = head[u];
    head[u] = edgeCnt;
}

void addQuery(int u, int v, int id) {
    queryTo[++queryCnt] = v;
    queryId[queryCnt] = id;
    queryNext[queryCnt] = queryHead[u];
    queryHead[u] = queryCnt;
}

int find(int u) {
    int r = u;
    while (dsu[r] != r) r = dsu[r];
    while (dsu[u] != u) {
        int next = dsu[u];
        dsu[u] = r;
        u = next;
    }
    return r;
}

void unite(int parent, int child) {
    int a = find(parent), b = find(child);
    if (a == b) return;
    if (dsuSize[a] < dsuSize[b]) swap(a, b);
    dsu[b] = a;
    dsuSize[a] += dsuSize[b];
    ancestor[a] = parent; // 合并后整个集合对应当前 DFS 中的父点。
}

void tarjan(int start) {
    int sp = 1;
    callStack[sp] = {start, 0, head[start]};
    while (sp) {
        Frame &frame = callStack[sp];
        int u = frame.u;
        if (frame.edge) {
            int e = frame.edge;
            frame.edge = nxt[e];
            int v = to[e];
            if (v == frame.parent) continue;
            callStack[++sp] = {v, u, head[v]};
        } else {
            finished[u] = true; // 当前点和它的子树均已处理。
            for (int e = queryHead[u]; e; e = queryNext[e]) {
                int v = queryTo[e];
                if (finished[v]) answer[queryId[e]] = ancestor[find(v)];
            }
            int parent = frame.parent;
            --sp;
            if (parent) unite(parent, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q >> root;
    for (int u = 1; u <= n; ++u) {
        dsu[u] = u;
        dsuSize[u] = 1;
        ancestor[u] = u;
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1, u, v; i <= q; ++i) {
        cin >> u >> v;
        addQuery(u, v, i);
        addQuery(v, u, i);
    }
    tarjan(root);
    for (int i = 1; i <= q; ++i) cout << answer[i] << '\n';
    return 0;
}
