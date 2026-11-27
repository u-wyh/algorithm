// https://www.luogu.com.cn/problem/P9173
// 题意：给定两个长度分别为 n 和 m 的 01 数组，将每个 0 替换为正偶数、每个 1 替换为正奇数，要求替换后两个数组均严格单调递增
// 且所有正整数至多使用一次。
// 最小化使用的最大数字并输出。
// 数据范围：0 <= n, m <= 5000。
// 算法标签：动态规划
#include <stdio.h>
#include <limits.h>

#define MAX_N 5005
#define INF 1000000000

int dp[MAX_N][MAX_N][2];
int n, m, a[MAX_N], b[MAX_N];

int main() {
    int i, j;

    // 输入
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d", &b[i]);
    }

    // 初始化dp数组
    for (i = 0; i <= n; ++i) {
        for (j = 0; j <= m; ++j) {
            dp[i][j][0] = dp[i][j][1] = INF;
            if (i == 0 && j == 0) continue; // 这种情况不存在

            if (i > 0) {
                dp[i][j][0] = (i > 1) ? dp[i-1][j][0] + 1 + (a[i] == a[i-1]) : 1 + (a[i] == a[i-1]);
                dp[i][j][0] = (j > 0) ? (dp[i][j][0] < dp[i-1][j][1] + 1 + (a[i] == b[j])) ? dp[i][j][0] : dp[i-1][j][1] + 1 + (a[i] == b[j]) : dp[i][j][0];
            }

            if (j > 0) {
                dp[i][j][1] = (j > 1) ? dp[i][j-1][1] + 1 + (b[j] == b[j-1]) : 1 + (b[j] == b[j-1]);
                dp[i][j][1] = (i > 0) ? (dp[i][j][1] < dp[i][j-1][0] + 1 + (b[j] == a[i])) ? dp[i][j][1] : dp[i][j-1][0] + 1 + (b[j] == a[i]) : dp[i][j][1];
            }
        }
    }

    // 输出最优方案
    printf("%d\n", (dp[n][m][0] < dp[n][m][1]) ? dp[n][m][0] : dp[n][m][1]);

    return 0;
}
