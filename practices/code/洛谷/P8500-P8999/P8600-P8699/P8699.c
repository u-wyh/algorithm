// https://www.luogu.com.cn/problem/P8699
// 题意：输入整数 n, k；
// 若 1..n 的排列中有 t 个元素同时小于或
// 同时大于左右相邻元素（即 t 个折点），则称其为 t+1 单调排列；
// 输出 1..n 的所有排列中 k 单调排列的数量对 123456 取模的结果。
// 数据范围：1 <= k <= n <= 500。
// 算法标签：动态规划
#include <stdio.h>
#include <string.h>

#define ll long long
#define MOD 123456

int dp[505][505];

int mod(int a) {
    return a % MOD;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i][0] = 2;
        for (int j = 0; j <= i; j++) {
            dp[i + 1][j] = (dp[i + 1][j] + mod(dp[i][j] * (j + 1))) % MOD;
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + mod(dp[i][j] * 2)) % MOD;
            if (j + 2 <= i) {
                dp[i + 1][j + 2] = (dp[i + 1][j + 2] + mod(dp[i][j] * (i - j - 2))) % MOD;
            }
        }
    }

    printf("%d\n", dp[n][k - 1]);
    return 0;
}
