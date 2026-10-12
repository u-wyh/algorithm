// 用途：维护无向图动态连通性，支持合并两个集合、查询是否同属一组。
// 时间：初始化 O(n)，单次操作均摊 O(α(n))。
// 空间：O(n)。
// 注意：点编号 1..n，n<=100000；输入 n q，操作 1 u v 为合并，2 u v 为查询。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int parentNode[MAXN], setSize[MAXN];

int findRoot(int x) {
    if (parentNode[x] == x) return x;
    return parentNode[x] = findRoot(parentNode[x]);
}

void unite(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x == y) return;
    if (setSize[x] < setSize[y]) swap(x, y);
    // 小集合挂到大集合，限制树高。
    parentNode[y] = x;
    setSize[x] += setSize[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    for (int i = 1; i <= n; ++i) parentNode[i] = i, setSize[i] = 1;
    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) unite(u, v);
        else cout << (findRoot(u) == findRoot(v) ? "Yes" : "No") << '\n';
    }
    return 0;
}
