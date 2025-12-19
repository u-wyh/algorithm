#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LL long long

#define N 30
#define M 110

LL dp[N][M][M], ans[N][2], num;
int n, m, q[N], len = 0;

LL turn(LL a, LL b) { // 快速幂
    LL s = 1;
    while (b) {
        if (b & 1) s *= a;
        a *= a;
        b >>= 1;
    }
    return s;
}

void deal() { // 预处理部分数组
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= len; ++i) {
        LL sum = q[i] * turn(10, i - 1);
        for (int k = 0; k <= n; ++k)
            dp[i][k][0] = dp[i - 1][k][0] + sum;
        for (int p = 0; p <= m; ++p)
            dp[i][0][p] = dp[i - 1][0][p] + sum;
    }
}

void solve(LL x) {
    memset(q, 0, sizeof(q));
    while (x) q[++len] = x % 10, x /= 10; // 处理数位
    deal();

    for (int i = 1; i <= len; ++i) { // 背包方式处理
        for (int j = q[i]; j <= 9; ++j) {
            int a = j - q[i], b = q[i] + 10 - j;
            LL sum = j * turn(10, i - 1);
            for (int k = 0; k <= n; ++k)
                for (int p = 0; p <= m; ++p) {
                    if (k >= a) dp[i][k][p] = (dp[i][k][p] > dp[i - 1][k - a][p] + sum) ? dp[i][k][p] : dp[i - 1][k - a][p] + sum;
                    if (p >= b) dp[i][k][p] = (dp[i][k][p] > dp[i - 1][k][p - b] + sum) ? dp[i][k][p] : dp[i - 1][k][p - b] + sum;
                }
        }
    }
}

int main() {
    scanf("%lld%d%d", &num, &n, &m);
    solve(num);
    printf("%lld\n", dp[len][n][m]); // 输出结果
    return 0;
}
