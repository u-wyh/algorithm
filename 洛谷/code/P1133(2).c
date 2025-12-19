#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100010

int dp[MAX_N][3][2], n;
int a[MAX_N][3];
int ans = 0;

// 自定义max函数
int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]); // 读入每个位置各种高度的观赏价值
    }

    // 初始化dp数组
    for (int j = 0; j < 3; j++) { // 穷举树的高度（有三种）这里的意思是第一个位置种下第j颗树
        for (int i = 0; i < 3; i++)
            for (int k = 0; k < 2; k++)
                dp[1][i][k] = 0;
        dp[1][j][0] = dp[1][j][1] = a[1][j]; // 初始值为a[1][j]

        for (int i = 2; i <= n; i++) { // 循环每个位置作决策
            dp[i][0][0] = max(dp[i-1][1][1], dp[i-1][2][1]) + a[i][0];
            dp[i][1][0] = dp[i-1][2][1] + a[i][1];
            dp[i][1][1] = dp[i-1][0][0] + a[i][1];
            dp[i][2][1] = max(dp[i-1][1][0], dp[i-1][0][0]) + a[i][2];
        }

        // 更新ans
        for (int i = 0; i < j; i++)
            ans = max(ans, dp[n][i][0]); // <=j的高度肯定是比它矮的，所以为dp[n][i][0]
        for (int i = 2; i > j; i--)
            ans = max(ans, dp[n][i][1]); // >j的肯定是比它高的，所以为dp[n][i][1]
    }

    printf("%d\n", ans); // 输出结果
    return 0;
}
