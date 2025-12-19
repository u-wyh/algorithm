#include <stdio.h>
#include <string.h>
#include <limits.h> // 为了使用INT_MIN

int n, m, k;
int p[505], b[505], dp[505][505];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i <= m; i++) {
        scanf("%d", &b[i]);
    }

    // 初始化dp数组，这里假设所有初始值为INT_MIN，表示未访问
    memset(dp, INT_MIN, sizeof(dp));
    // 初始化dp[0][0]为0，表示没有选择任何物品时的价值为0
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            // 假设当前dp[i][j]为最小值，通过比较更新为最大值
            dp[i][j] = INT_MIN;
            for (int kk = 0; kk <= j; kk++) {
                // 注意数组下标调整，因为p[i]是从1开始的，而b的下标是从0开始的
                int index = p[i] + j - kk;
                if (index >= 0 && index <= m) {
                    // 只有在index有效时才进行计算
                    dp[i][j] = (dp[i][j] > dp[i-1][kk] + b[index]) ? dp[i][j] : (dp[i-1][kk] + b[index]);
                }
            }
        }
    }

    // 输出结果，如果dp[n][k]仍然是INT_MIN，则表示没有可行的解决方案
    if (dp[n][k] == INT_MIN) {
        printf("No valid solution.\n");
    } else {
        printf("%d\n", dp[n][k]);
    }

    return 0;
}
