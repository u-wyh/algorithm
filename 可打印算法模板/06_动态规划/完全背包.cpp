// 用途：每种物品可选任意次，在容量 W 内求最大总价值。
// 时间：O(nW)。
// 空间：O(W)。
// 注意：输入 n W 和 n 组正体积、价值；n<=1000，W<=100000；容量必须正序更新。
#include <bits/stdc++.h>
using namespace std;

const int MAXW = 100005;
long long dp[MAXW];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, W;
    if (!(cin >> n >> W)) return 0;
    for (int i = 0; i < n; ++i) {
        int weight;
        long long value;
        cin >> weight >> value;
        // 正序允许当前物品接着当前物品继续转移。
        for (int cap = weight; cap <= W; ++cap)
            dp[cap] = max(dp[cap], dp[cap - weight] + value);
    }
    cout << dp[W] << '\n';
    return 0;
}
