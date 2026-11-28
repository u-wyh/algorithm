// https://codeforces.com/problemset/problem/490/F
// 题意：n 点树，每个点有权值 r_i，求树上最长严格上升子序列长度。
// 输出：任意简单路径上点权严格递增子序列的最大长度。
// 数据范围：2 <= n <= 6000，1 <= r_i <= 10^6。
// 难度评分：2200（CF 官方）
// 算法标签：深度优先搜索、最长上升子序列、二分查找
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 6005;
vector<int> adj[MAXN];
int r[MAXN], tails[MAXN];
int ans = 1;

void dfs(int u, int parent, int len){
    // tails[k] 是当前路径上长度为 k+1 的递增子序列的最小末值。
    int pos = len;
    if (len != 0 && r[u] <= tails[len - 1]){
        pos = lower_bound(tails, tails + len, r[u]) - tails;
    }
    int prev = tails[pos];
    tails[pos] = r[u];
    len = max(len, pos + 1);
    ans = max(ans, len);

    for (int v : adj[u]){
        if (v != parent){
            dfs(v, u, len);
        }
    }
    tails[pos] = prev;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> r[i];
    }
    for (int i = 1; i < n; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++){
        dfs(i, 0, 0);
    }
    cout << ans << '\n';
    return 0;
}