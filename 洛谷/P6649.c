#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 1000 + 84
#define LL long long

long long min(long long a,long long b)
{
    return a<b?a:b;
}

LL n, m, ans = LLONG_MAX, val[MAXN][MAXN], f[MAXN][MAXN], hzn[MAXN], qzn[MAXN];

int main() {
    scanf("%lld%lld", &n, &m);
    for (LL i = n; i >= 1; i--) {
        for (LL j = 1; j <= m; j++) {
            scanf("%lld", &val[i][j]);
        }
    }

    for (LL i = 1; i <= n; i++) {
        memset(hzn, 0x7f, sizeof(hzn));
        memset(qzn, 0x7f, sizeof(qzn));
        qzn[0] = 0LL; // 初始化qzn[0]为0，用于计算前缀最小值
        for (LL j = 1; j <= m; j++) {
            qzn[j] = (j > 0 ? min(qzn[j - 1], 0LL) : 0LL) + val[i][j];
        }
        for (LL j = m; j >= 1; j--) {
            if (i > 1) {
                hzn[j] = min(hzn[j + 1], f[i - 1][j]) + val[i][j];
            } else {
                hzn[j] = val[i][j]; // 第一行没有上一行的数据，直接取当前值
            }
        }
        for (LL j = 1; j <= m; j++) {
            f[i][j] = min(hzn[j] + qzn[j] - val[i][j], hzn[j]);
        }
    }

    for (LL i = 1; i <= m; i++) {
        ans = min(ans, f[n][i]);
    }

    printf("%lld\n", ans);
    return 0;
}
