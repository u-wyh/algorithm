#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<vector<int>> graph(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> parent(n + 1, 0);
        vector<int> depth(n + 1, -1);
        vector<vector<int>> children(n + 1);
        vector<vector<int>> level_nodes(n + 1);
        int max_depth = 0;

        queue<int> q;
        q.push(1);
        depth[1] = 0;
        level_nodes[0].push_back(1);
        parent[1] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                if (depth[v] > max_depth) max_depth = depth[v];
                level_nodes[depth[v]].push_back(v);
                children[u].push_back(v);
                q.push(v);
            }
        }

        vector<LL> val(n + 1, 0);
        vector<LL> dp(n + 1, 0);

        for (int d = max_depth; d >= 0; d--) {
            for (int u : level_nodes[d]) {
                if (children[u].empty()) {
                    val[u] = 0;
                    dp[u] = 0;
                } else {
                    vector<int> vals;
                    for (int v : children[u]) {
                        vals.push_back(val[v]);
                    }
                    int cnt = vals.size();
                    vector<bool> seen(cnt + 2, false);
                    for (int x : vals) {
                        if (x <= cnt + 1) {
                            seen[x] = true;
                        }
                    }
                    int mex = 0;
                    while (mex <= cnt + 1 && seen[mex]) {
                        mex++;
                    }
                    val[u] = mex;
                    dp[u] = val[u];
                    for (int v : children[u]) {
                        dp[u] += dp[v];
                    }
                }
            }
        }

        cout << dp[1] << '\n';
    }
    return 0;
}