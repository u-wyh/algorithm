// https://codeforces.com/problemset/problem/490/F
// 题意：n 点树，每个点有权值 r_i，求树上最长严格上升子序列长度。
// 输出：任意简单路径上点权严格递增子序列的最大长度。
// 数据范围：2 <= n <= 6000，1 <= r_i <= 10^6。
// 算法标签：深度优先搜索、动态规划
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 6005;
vector<int> adj[MAXN];
int r[MAXN], dp[MAXN];
int ans = 1;

void dfs(int u, int parent) {
    for (int v : adj[u]) {
        if (v == parent) continue;
        if (r[v] > r[u]) {
            if (dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
                ans = max(ans, dp[v]);
                dfs(v, u);
            }
        } else {
            dfs(v, u);
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
        dp[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i, -1);
    }
    cout << ans << endl;
    return 0;
}