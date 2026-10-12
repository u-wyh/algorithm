// 用途：函数图按连通块分解基环树，统计无有向环的边定向方案数。
// 时间：O(n α(n))。
// 空间：O(n)。
// 注意：n<=2e5；自环无合法方案；剥叶代替长链递归 DFS。
// 例题：https://www.luogu.com.cn/problem/CF711D
// 题意：函数图的边重新定向，统计没有有向环的方案。
// 思路：每个连通块是一棵基环树；环的两个全同向方案需排除。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MOD = 1000000007;
int n, to[MAXN], indegree[MAXN], que[MAXN];
int parentNode[MAXN], setSize[MAXN], componentSize[MAXN], cycleSize[MAXN];
long long powerTwo[MAXN];

int findRoot(int x) {
    if (parentNode[x] == x) return x;
    return parentNode[x] = findRoot(parentNode[x]);
}

void unite(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x == y) return;
    if (setSize[x] < setSize[y]) swap(x, y);
    parentNode[y] = x;
    setSize[x] += setSize[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) parentNode[i] = i, setSize[i] = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> to[i];
        ++indegree[to[i]];
        unite(i, to[i]);
    }

    // 度数归零的点都在环外；剥完后剩下的正是各连通块的环。
    int left = 0, right = 0;
    for (int i = 1; i <= n; ++i)
        if (indegree[i] == 0) que[right++] = i;
    while (left < right) {
        int u = que[left++];
        if (--indegree[to[u]] == 0) que[right++] = to[u];
    }

    powerTwo[0] = 1;
    for (int i = 1; i <= n; ++i) powerTwo[i] = powerTwo[i - 1] * 2 % MOD;
    for (int i = 1; i <= n; ++i) {
        int root = findRoot(i);
        ++componentSize[root];
        if (indegree[i] > 0) ++cycleSize[root];
    }

    long long answer = 1;
    for (int i = 1; i <= n; ++i) {
        if (parentNode[i] != i) continue;
        int treeEdges = componentSize[i] - cycleSize[i];
        // 环的两个同向方案非法；树枝上的方向可独立选择。
        long long ways = (powerTwo[cycleSize[i]] - 2 + MOD) % MOD;
        answer = answer * ways % MOD * powerTwo[treeEdges] % MOD;
    }
    cout << answer << '\n';
    return 0;
}
