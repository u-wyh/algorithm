// 用途：对多个闭区间加值后一次性求所有位置的值。
// 时间：O(n+m)。
// 空间：O(n)。
// 注意：下标从 1 开始；n<=1e6。
// 例题：https://leetcode.cn/problems/corporate-flight-bookings/
// 题意：多次给闭区间加值，最后输出各位置结果。
// 思路：每次只改区间首尾差分，最后取前缀和恢复数组。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
// 闭区间 [l,r] 加 v：在 l 加 v、r+1 减 v。
long long diff[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    for (int i = 0, l, r; i < m; ++i) {
        long long v;
        cin >> l >> r >> v;
        diff[l] += v;
        diff[r + 1] -= v;
    }
    for (int i = 1; i <= n; ++i) {
        diff[i] += diff[i - 1];
        if (i > 1) cout << ' ';
        cout << diff[i];
    }
    cout << '\n';
    return 0;
}
