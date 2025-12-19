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