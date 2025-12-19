#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 3005;
const long long MOD = 998244353;

long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long inv(long long x) {
    return qpow(x, MOD - 2);
}

int n;
vector<int> G[MAXN];
long long a[MAXN], b[MAXN], p[MAXN];
vector<long long> dp[MAXN];
int parent[MAXN];
vector<int> children[MAXN];
long long ans[MAXN];

void dfs_build(int u, int pre, int root) {
    parent[u] = pre;
    children[u].clear();
    for (int v : G[u]) {
        if (v == pre) continue;
        children[u].push_back(v);
        dfs_build(v, u, root);
    }
}

void dfs_dp(int u) {
    if (children[u].empty()) {
        dp[u] = vector<long long>(2);
        dp[u][0] = (1 - p[u] + MOD) % MOD;
        dp[u][1] = p[u];
        return;
    }

    int max_len = 0;
    for (int v : children[u]) {
        dfs_dp(v);
        max_len = max(max_len, (int)dp[v].size());
    }

    vector<long long> surv(max_len + 1, 1);
    for (int k = 0; k <= max_len; k++) {
        for (int v : children[u]) {
            long long s = 0;
            if (k < (int)dp[v].size()) {
                for (int j = k; j < (int)dp[v].size(); j++) {
                    s = (s + dp[v][j]) % MOD;
                }
            }
            surv[k] = surv[k] * s % MOD;
        }
    }

    vector<long long> min_dist(max_len + 1, 0);
    for (int k = 0; k < max_len; k++) {
        min_dist[k] = (surv[k] - surv[k + 1] + MOD) % MOD;
    }
    min_dist[max_len] = surv[max_len];

    dp[u] = vector<long long>(max_len + 2, 0);
    for (int k = 0; k <= max_len; k++) {
        dp[u][k] = (dp[u][k] + (1 - p[u] + MOD) % MOD * min_dist[k]) % MOD;
        if (k + 1 <= max_len + 1) {
            dp[u][k + 1] = (dp[u][k + 1] + p[u] * min_dist[k]) % MOD;
        }
    }
}

void reroot(int from, int to) {
    vector<long long> old_dp_from = dp[from];
    vector<long long> old_dp_to = dp[to];
    vector<int> old_children_from = children[from];
    vector<int> old_children_to = children[to];

    children[from].erase(remove(children[from].begin(), children[from].end(), to), children[from].end());
    children[to].push_back(from);

    auto update_dp = [](int u) {
        if (children[u].empty()) {
            dp[u] = vector<long long>(2);
            dp[u][0] = (1 - p[u] + MOD) % MOD;
            dp[u][1] = p[u];
            return;
        }

        int max_len = 0;
        for (int v : children[u]) {
            max_len = max(max_len, (int)dp[v].size());
        }

        vector<long long> surv(max_len + 1, 1);
        for (int k = 0; k <= max_len; k++) {
            for (int v : children[u]) {
                long long s = 0;
                if (k < (int)dp[v].size()) {
                    for (int j = k; j < (int)dp[v].size(); j++) {
                        s = (s + dp[v][j]) % MOD;
                    }
                }
                surv[k] = surv[k] * s % MOD;
            }
        }

        vector<long long> min_dist(max_len + 1, 0);
        for (int k = 0; k < max_len; k++) {
            min_dist[k] = (surv[k] - surv[k + 1] + MOD) % MOD;
        }
        min_dist[max_len] = surv[max_len];

        dp[u] = vector<long long>(max_len + 2, 0);
        for (int k = 0; k <= max_len; k++) {
            dp[u][k] = (dp[u][k] + (1 - p[u] + MOD) % MOD * min_dist[k]) % MOD;
            if (k + 1 <= max_len + 1) {
                dp[u][k + 1] = (dp[u][k + 1] + p[u] * min_dist[k]) % MOD;
            }
        }
    };

    update_dp(from);
    update_dp(to);
}

void compute_ans(int root) {
    dfs_build(root, -1, root);
    dfs_dp(root);
    long long res = 0;
    for (int k = 0; k < (int)dp[root].size(); k++) {
        res = (res + (long long)k * dp[root][k]) % MOD;
    }
    ans[root] = res;
}

void dfs_reroot(int u, int pre) {
    for (int v : G[u]) {
        if (v == pre) continue;
        reroot(u, v);
        long long res = 0;
        for (int k = 0; k < (int)dp[v].size(); k++) {
            res = (res + (long long)k * dp[v][k]) % MOD;
        }
        ans[v] = res;
        dfs_reroot(v, u);
        // reroot(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        p[i] = a[i] * inv(b[i]) % MOD;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    compute_ans(0);
    long long res0 = 0;
    for (int k = 0; k < (int)dp[0].size(); k++) {
        res0 = (res0 + (long long)k * dp[0][k]) % MOD;
    }
    ans[0] = res0;
    dfs_reroot(0, -1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? '\n' : ' ');
    }

    return 0;
}