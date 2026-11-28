// https://codeforces.com/problemset/problem/1731/E
// 题意：每组给 n 个点，初始没有边。
// 边 (u, v) 的权是 gcd(u, v)。
// 一次可花 k+1 的费用，加入恰好 k 条权为 k+1 的边。
// 禁止自环、重边，目标是恰有 m 条边。
// 输出：每组输出最少费用，无法达成输出 -1。
// 数据范围：1 <= t <= 10^4，2 <= n <= 10^6，
// 1 <= m <= n*(n-1)/2。
// 所有组的 n 之和不超过 10^6。
// 难度评分：2000（CF 官方）
// 算法标签：欧拉函数、贪心
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int MAX_N = 1000000;

vector<ll> phi_sum(MAX_N + 1);

void precompute() {
    vector<int> phi(MAX_N + 1);
    for (int i = 1; i <= MAX_N; i++) {
        phi[i] = i;
    }
    for (int i = 2; i <= MAX_N; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= MAX_N; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    phi_sum[0] = 0;
    for (int i = 1; i <= MAX_N; i++) {
        phi_sum[i] = phi_sum[i - 1] + phi[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    precompute();
    int t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        ll M_max_real = 0;
        for (ll d = 2; d <= n; d++) {
            ll c = n / d;
            if (c < 2) {
                continue;
            }
            ll avail = phi_sum[c] - 1;
            ll volume = d - 1;
            ll max_ops_d = avail / volume;
            ll edges_d = max_ops_d * volume;
            M_max_real += edges_d;
        }
        if (m > M_max_real) {
            cout << -1 << '\n';
            continue;
        }
        ll cost = 0;
        ll rem = m;
        for (ll d = n; d >= 2; d--) {
            ll volume = d - 1;
            ll c = n / d;
            if (c < 2) {
                continue;
            }
            ll avail = phi_sum[c] - 1;
            ll max_ops_d = avail / volume;
            if (max_ops_d == 0) {
                continue;
            }
            ll ops = rem / volume;
            if (ops > max_ops_d) {
                ops = max_ops_d;
            }
            cost += ops * d;
            rem -= ops * volume;
            if (rem == 0) {
                break;
            }
        }
        cout << cost << '\n';
    }
    return 0;
}