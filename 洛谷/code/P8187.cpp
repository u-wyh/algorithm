// https://www.luogu.com.cn/problem/P8187
// 题意：机器人从 (0,0) 出发，给定 N 条位移向量指令 (x_i, y_i) 和终点 (x_g, y_g)。
// 对每个 K = 1..N，求从这 N 条指令中选出 K 条使其和恰好为 (x_g, y_g) 的方案数。
// 数据范围：1 <= N <= 40，-10^9 <= x_g, y_g, x_i, y_i <= 10^9
// 保证 (x_g, y_g) != (0,0) 且对所有 i 有 (x_i, y_i) != (0,0)。
// 算法标签：折半搜索、深度优先搜索
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define int long long

int n;
int X[42], Y[42];
map<pair<int, int>, map<int, int>> cntMap; // {x,y} -> {count: 使用k个向量的方案数}
int ans[42];

void dfs1(int u, int x, int y, int now) {
    if (u == n/2 + 1) {
        cntMap[{x, y}][now]++;
        return;
    }
    dfs1(u + 1, x + X[u], y + Y[u], now + 1);
    dfs1(u + 1, x, y, now);
}

void dfs2(int u, int x, int y, int now) {
    if (u == n + 1) {
        auto it = cntMap.find({X[n+1] - x, Y[n+1] - y});
        if (it != cntMap.end()) {
            for (auto& p : it->second) {
                ans[now + p.first] += p.second;
            }
        }
        return;
    }
    dfs2(u + 1, x + X[u], y + Y[u], now + 1);
    dfs2(u + 1, x, y, now);
}

signed main() {
    cin >> n;
    cin >> X[n+1] >> Y[n+1];
    for (int i = 1; i <= n; i++) {
        cin >> X[i] >> Y[i];
    }
    dfs1(1, 0, 0, 0);
    dfs2(n/2 + 1, 0, 0, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}