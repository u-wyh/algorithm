#include <bits/stdc++.h>
using namespace std;

const int N = 1e6, L = __lg(N) + 1;
int n, n2, m, op[N + 5], f[L][N + 5];
pair<int, int> s[N + 5];  // 限制a,b

pair<int, int> dfs(int p, int l, int r, int d) {
    if (l == r) return {0, 0};
    
    int m = (l + r) >> 1;
    pair<int, int> L = dfs(p << 1, l, m, d - 1);
    pair<int, int> R = dfs(p << 1 | 1, m + 1, r, d - 1);
    pair<int, int> ans = {n2, n2};
    
    if (op[p] == 1) {
        for (int i = l; i <= m; ++i) s[i].first += R.first + 1;
        for (int i = m + 1; i <= r; ++i) s[i].first += L.first + 1;
    } else {
        for (int i = l; i <= m; ++i) s[i].second += R.second + 1;
        for (int i = m + 1; i <= r; ++i) s[i].second += L.second + 1;
    }
    
    for (int i = l; i <= r; ++i) {
        ans.first = min(ans.first, s[i].first);
        ans.second = min(ans.second, s[i].second);
        ++f[d][s[i].first + 1];
        --f[d][n2 - s[i].second + 1];
    }
    
    return ans;  // 返回区间的最优限制
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    n2 = 1 << n;
    
    for (int i = 1; i < n2; ++i) 
		cin >> op[i];
    
    dfs(1, 1, n2, n);
    
    f[0][0] = 1;  // 记得处理第一场比赛啊
    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= n2; ++j) {
            f[i][j] += f[i][j - 1];
        }
    }
    
    while (m--) {
        int a, b;
        cin >> a >> b;
        cout << (f[b - 1][a] > 0 ? "Yes\n" : "No\n");
    }
    
    return 0;
}