// 用途：树上最低公共祖先；输入 n m root、树边与询问。
// 时间：预处理 O(n)，单次查询 O(log n)。
// 空间：O(n)。
// 注意：n<=5e5；长链用显式遍历避免递归爆栈。
// 例题：https://www.luogu.com.cn/problem/P3379
// 题意：多次询问树上两个点的最近公共祖先。
// 思路：反复跳较深链的链顶，直到两点同链。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int n, m, root;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cnt = 0;

int fa[MAXN];
int dep[MAXN];
int siz[MAXN];
// son 是最大子树儿子，top 是所在重链的链顶。
int son[MAXN];
int top[MAXN];

void addEdge(int u, int v) {
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

int order[MAXN], work[MAXN];

void build() {
    int len = 1;
    order[0] = root;
    dep[root] = 1;
    for (int i = 0; i < len; ++i) {
        int u = order[i];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == fa[u]) continue;
            fa[v] = u;
            dep[v] = dep[u] + 1;
            order[len++] = v;
        }
    }
    for (int i = len - 1; i >= 0; --i) {
        int u = order[i];
        siz[u] = 1;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (fa[v] != u) continue;
            siz[u] += siz[v];
            if (!son[u] || siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    int sp = 0;
    work[sp++] = root;
    while (sp) {
        int chainRoot = work[--sp];
        for (int u = chainRoot; u; u = son[u]) {
            top[u] = chainRoot;
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                if (fa[v] == u && v != son[u]) work[sp++] = v;
            }
        }
    }
}

int lca(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] <= dep[top[b]]) {
            b = fa[top[b]];
        } else {
            a = fa[top[a]];
        }
    }
    return dep[a] <= dep[b] ? a : b;//在一条重链上  深度小的是lca
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> root;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    build();
    for (int i = 1, a, b; i <= m; i++) {
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
    return 0;
}
