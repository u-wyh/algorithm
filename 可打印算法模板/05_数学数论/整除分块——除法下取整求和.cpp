// 用途：利用相同商组成的连续区间，快速求 Σ floor(n/i)，i 从 1 到 n。
// 时间：O(√n)。
// 空间：O(1)。
// 注意：n≤10^12，返回值使用 long long；n≤0 时返回 0。
// 例题：https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2521
// 题意：求从 i=1 到 n 的 floor(n/i) 总和。
// 思路：商相同的下标形成连续段，按段一次累加。
#include <bits/stdc++.h>
using namespace std;

long long quotientSum(long long n) {
    long long answer = 0;
    for (long long left = 1, right; left <= n; left = right + 1) {
        long long quotient = n / left;
        right = n / quotient; // [left, right] 中 floor(n/i) 不变。
        answer += quotient * (right - left + 1);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        long long n;
        cin >> n;
        cout << quotientSum(n) << '\n';
    }
    return 0;
}
