// https://www.luogu.com.cn/problem/P2513
// 题意：求 1~n 的排列中逆序对数恰好为 k 的排列个数。
// 输出方案数对 10000 取模的结果。
// 数据范围：n <= 1000，k <= 1000。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 算法标签：动态规划、前缀和

#define ll long long
#define MODE 10000

ll dp[1005][1005];
ll s[1005][1005];//表示前缀和
ll n, k;

int main() {
    scanf("%lld %lld", &n, &k);
    dp[1][0] = 1;
    for (int i = 0; i <= k; i++) {
        s[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= (n * (n - 1) / 2) && j <= k; j++) {
            if (j - i < 0) {
                dp[i][j] = s[i - 1][j];
            } else {
                dp[i][j] = (s[i - 1][j] - s[i - 1][j - i] + MODE) % MODE;
            }
        }

        s[i][0] = dp[i][0];
        for (int j = 1; j <= k; j++) {
            s[i][j] = (s[i][j - 1] + dp[i][j]) % MODE;
        }
    }

    printf("%lld\n", dp[n][k]);
    return 0;
}
