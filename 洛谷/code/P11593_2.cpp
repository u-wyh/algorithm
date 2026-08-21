#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

int n, m, tot;
int d[MAXN];
int fa[MAXN];
int sz[MAXN];
int dp[MAXN];
bool active[MAXN];

vector<int> child[MAXN];

// 并查集查找：找到当前连通块代表点
int findfa(int x) {
    if (fa[x] == x) return x;
    return fa[x] = findfa(fa[x]);
}

// 判断一个格子是否在边界上
bool isEdge(int id) {
    int x = id / m;
    int y = id % m;
    return x == 0 || x == n - 1 || y == 0 || y == m - 1;
}

// 枚举四个相邻格子
void getNeighbors(int id, vector<int>& nb) {
    nb.clear();

    int x = id / m;
    int y = id % m;

    if (x > 0) nb.push_back((x - 1) * m + y);
    if (x + 1 < n) nb.push_back((x + 1) * m + y);
    if (y > 0) nb.push_back(x * m + y - 1);
    if (y + 1 < m) nb.push_back(x * m + y + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    tot = n * m;

    vector<int> ord(tot);

    for (int i = 0; i < tot; i++) {
        cin >> d[i];
        fa[i] = i;
        ord[i] = i;
    }

    // 按耐久度从大到小加入格子
    sort(ord.begin(), ord.end(), [](int a, int b) {
        return d[a] > d[b];
    });

    vector<int> nb;

    for (int u : ord) {
        active[u] = true;

        getNeighbors(u, nb);

        for (int v : nb) {
            if (!active[v]) continue;

            int root = findfa(v);

            // 如果这个连通块已经挂到 u 下面了，就不用重复处理
            if (root == u) continue;

            // 把原来的连通块 root 作为 u 的儿子
            fa[root] = u;
            child[u].push_back(root);
        }
    }

    // 计算每个重构树节点的子树大小
    for (int u : ord) {
        sz[u] = 1;

        for (int v : child[u]) {
            sz[u] += sz[v];
        }
    }

    // DP 要从低耐久节点向高耐久节点传，所以反过来遍历
    reverse(ord.begin(), ord.end());

    int ans = 0;

    for (int u : ord) {
        // 如果 u 是边缘格子，可以选择在这里结束
        if (isEdge(u)) {
            ans = max(ans, min(dp[u] + sz[u], d[u]));
        }

        for (int v : child[u]) {
            /*
                从 u 进入儿子 v 的连通块时：
                可以先收集 u 这一层中，除了 v 子树之外的金币。
                但经过 u 时，金币数不能超过 d[u]。
            */
            dp[v] = min(dp[u] + sz[u] - sz[v], d[u]);
        }
    }

    cout << ans << '\n';

    return 0;
}