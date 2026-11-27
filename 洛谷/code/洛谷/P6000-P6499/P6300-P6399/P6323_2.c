// https://www.luogu.com.cn/problem/P6323
// 题意：求长度为 n 且逆序对数量恰好为 c 的排列总数，
// 答案对 10^9+7 取模。
// 数据范围：1 <= n <= 10^3，1 <= c <= 10^4。
// 算法标签：动态规划、前缀和
#include <stdio.h>

#define MOD 1000000007

int n, c;
int dp[10004], s[10004];

int main() {
    scanf("%d %d", &n, &c);
    dp[0] = 1;

    for (int i = 2; i <= n; i++) {
        s[0] = dp[0];
        for (int j = 1; j <= c; j++) {
            s[j] = (s[j - 1] + dp[j]) % MOD;
        }

        for (int j = 0; j <= c; j++) {
            if (j >= i) {
                dp[j] = (s[j] - s[j - i] + MOD) % MOD;
            } else {
                dp[j] = s[j];
            }
        }
    }

    printf("%d\n", dp[c]);
    return 0;
}
