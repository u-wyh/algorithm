#include <stdio.h>

#define MODNUM 1000000007
#define MAXN 7001

long long n, m;
unsigned int dp[MAXN][MAXN];
long long sum[MAXN];
long long a[MAXN];

int main() {
    long long i, j, k;
    scanf("%lld %lld", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%lld", &a[i]);
    }
    if (m == 1 && a[1] < n) {
        printf("0\n");
        return 0;
    }

    // 初始化dp数组和sum数组
    for (i = 1; i <= m; i++) {
        dp[1][i] = 1;
    }
    sum[1] = m;

    // 动态规划填充dp和sum数组
    for (i = 2; i <= n; i++) {
        sum[i] = 0; // 每次循环前重置sum[i]
        for (j = 1; j <= m; j++) {
            dp[i][j] = sum[i - 1];
            if (i > a[j]) {
                if (i == a[j] + 1) {
                    dp[i][j] = (dp[i][j] - 1 + MODNUM) % MODNUM;
                } else {
                    dp[i][j] = (dp[i][j] - (sum[i - a[j] - 1] - (j > a[j] + 1 ? dp[i - a[j] - 1][j] : 0)) + MODNUM) % MODNUM;
                }
            }
            sum[i] = (sum[i] + dp[i][j]) % MODNUM;
        }
    }

    printf("%lld\n", sum[n]);
    return 0;
}
