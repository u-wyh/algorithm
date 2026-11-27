// https://www.luogu.com.cn/problem/P10376
// 题意：拿一个初值为 n 的数，每轮选择减 a 或减 b，第一次变成不大于 c 时立刻停。
// 求不同操作序列的个数，对 10^9+7 取模。
// a 等于 b 时两种操作也要区分。
// 数据范围：1 ≤ a,b,c ≤ n ≤ 2 × 10^5。
// 算法标签：动态规划

#include <stdio.h>

#define MOD 1000000007

long long s[200005];

int main() {
    int n, a, b, c;
    long long ans = 0;
    scanf("%d %d %d %d", &n, &a, &b, &c);

    if (n == c) { // 特判
        printf("1\n");
        return 0;
    }

    s[n] = 1;
    for (int i = n; i > c; i--) {
        if (i - a > c) {
            s[i - a] = (s[i - a] + s[i]) % MOD;
        } else {
            ans = (ans + s[i]) % MOD;
        }

        if (i - b > c) {
            s[i - b] = (s[i - b] + s[i]) % MOD;
        } else {
            ans = (ans + s[i]) % MOD;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
