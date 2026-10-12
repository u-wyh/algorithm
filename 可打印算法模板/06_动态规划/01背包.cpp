// 用途：每件物品最多选一次，在容量 W 内求最大总价值。
// 时间：O(nW)。
// 空间：O(W)。
// 注意：输入 n W 和 n 组体积、价值；n<=1000，W<=100000；容量必须倒序更新。
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
        // 倒序使当前物品不会在同一轮重复使用。
        for (int cap = W; cap >= weight; --cap)
            dp[cap] = max(dp[cap], dp[cap - weight] + value);
    }
    cout << dp[W] << '\n';
    return 0;
}
