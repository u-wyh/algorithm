#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 2510
#define INF 0x3f3f3f3f

int n, m;
int sum[3][MAXN];
int dp[MAXN];
int a[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    memset(dp, INF, sizeof(dp)); // 使用memset初始化dp数组为无穷大
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[a[i]][i] = sum[a[i]][i - 1] + 1; // 累加当前数字出现的次数
        sum[!(a[i] - 1) + 1][i] = sum[!(a[i] - 1) + 1][i - 1]; // 对于a[i]-1为0或1的情况进行累加
        if (a[i] == 1) sum[2][i] = sum[2][i - 1] + 1; // 如果a[i]是1，则也更新sum[2]
    }

    // 注意：C语言中数组索引从0开始，但在这里我们保持从1开始的逻辑
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if ((abs(sum[2][i] - sum[1][i] - (sum[2][j] - sum[1][j])) <= m) ||
                (sum[2][i] - sum[2][j] == 0) ||
                (sum[1][i] - sum[1][j] == 0)) {
                dp[i] = (dp[i] < dp[j] + 1) ? dp[i] : dp[j] + 1;
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}
