// 用途：多次将树上两点路径的所有点加一，求最终最大点权。
// 时间：O((n+q) log n)。
// 空间：O(n log n)。
// 注意：n≤50000；点差分需在 LCA 和其父节点各减一。
// 例题：https://www.luogu.com.cn/problem/P3128
// 题意：多条树上路径每个点加一，求最大累计值。
// 思路：每次在端点和 LCA 附近做差分，后序汇总子树贡献。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005, LOG = 17;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edgeCount;
int parentJump[MAXN][LOG], depth[MAXN], order[MAXN];
long long delta[MAXN];

void addEdge(int u, int v) {
    to[++edgeCount] = v;
    nxt[edgeCount] = head[u];
    head[u] = edgeCount;
}

void prepare() {
    // 记录从根出发的遍历序；后面逆序累加子树差分值。
    int count = 1;
    order[0] = 1;
    depth[1] = 1;
    for (int i = 0; i < count; ++i) {
        int u = order[i];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == parentJump[u][0]) continue;
            parentJump[v][0] = u;
            depth[v] = depth[u] + 1;
            for (int j = 1; j < LOG; ++j)
                parentJump[v][j] = parentJump[parentJump[v][j - 1]][j - 1];
            order[count++] = v;
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int j = 0; j < LOG; ++j)
        if (diff & (1 << j)) u = parentJump[u][j];
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; --j) {
        if (parentJump[u][j] != parentJump[v][j]) {
            u = parentJump[u][j];
            v = parentJump[v][j];
        }
    }
    return parentJump[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    prepare();
    for (int i = 0, u, v; i < q; ++i) {
        cin >> u >> v;
        int p = lca(u, v);
        // 点差分：[u,v] 两端加，LCA 与 LCA 的父节点各减一。
        ++delta[u];
        ++delta[v];
        --delta[p];
        --delta[parentJump[p][0]];
    }
    long long answer = 0;
    for (int i = n - 1; i >= 0; --i) {
        // 后序把子树增量汇给父节点，此时 delta[u] 就是最终点权。
        int u = order[i];
        answer = max(answer, delta[u]);
        delta[parentJump[u][0]] += delta[u];
    }
    cout << answer << '\n';
    return 0;
}
