// 用途：求带权树中至少经过一条边的最大路径和；允许负边。
// 时间：O(n)。
// 空间：O(n)。
// 注意：n≤200000；两遍最远点搜索在有负边时不成立，n=1 时返回 0。
// 例题：https://www.luogu.com.cn/problem/U81904
// 题意：允许负边，求树上至少含一条边的最大路径和。
// 思路：后序求每点向下最优贡献，合并最大的两条分支更新答案。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], weight[MAXN * 2], edgeCount;
int parentNode[MAXN], order[MAXN];
long long down[MAXN];

void addEdge(int u, int v, int w) {
    to[++edgeCount] = v;
    weight[edgeCount] = w;
    nxt[edgeCount] = head[u];
    head[u] = edgeCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    // 先取得父子顺序，再逆序做树形 DP；长链不会耗尽递归栈。
    int count = 1;
    order[0] = 1;
    for (int i = 0; i < count; ++i) {
        int u = order[i];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == parentNode[u]) continue;
            parentNode[v] = u;
            order[count++] = v;
        }
    }
    long long answer = LLONG_MIN;
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        long long first = LLONG_MIN, second = LLONG_MIN;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (parentNode[v] != u) continue;
            long long branch = weight[e] + down[v];
            answer = max(answer, branch);
            if (branch > first) {
                second = first;
                first = branch;
            } else if (branch > second) {
                second = branch;
            }
        }
        if (second != LLONG_MIN) answer = max(answer, first + second);
        down[u] = max(0LL, first); // 父节点可选择不延伸到 u 的子树。
    }
    cout << (n == 1 ? 0 : answer) << '\n';
    return 0;
}
