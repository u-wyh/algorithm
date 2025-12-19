#include <stdio.h>
#include <limits.h> // 用于定义INT_MAX

#define MIN(a, b) ((a) < (b) ? (a) : (b))

long long dp[2000][2000];
long long a[2000][2000];

// 快速读入函数
int read() {
    int x = 0;
    int f = 0; // 使用int来表示正负标志
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        f |= (ch == '-');
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    if (f) return -x;
    else return x;
}

int main() {
    int n, m;
    n = read();
    m = read();

    // 初始化dp数组为一个大数（注意：这里使用LONG_LONG_MAX，但根据题目可能需要更大的数）
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m + 1; j++) {
            dp[i][j] = LLONG_MAX;
        }
    }

    // 读取矩阵a
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = read();
            if (j > 1 && a[i][j - 1] < 0) {
                a[i][j] += a[i][j - 1];
            }
        }
        dp[i][m + 1] = LLONG_MAX; // 边界条件
    }

    // 动态规划求解
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            if (a[i][j] <= 0) {
                dp[i][j] = MIN(dp[i][j + 1], dp[i + 1][j] + a[i][j]);
            } else {
                dp[i][j] = MIN(dp[i][j + 1], dp[i + 1][j]) + a[i][j];
            }
        }
    }

    // 找出第一行的最小值作为答案
    long long ans = LLONG_MAX;
    for (int j = 1; j <= m; j++) {
        ans = MIN(ans, dp[1][j]);
    }

    printf("%lld\n", ans);
    return 0;
}
