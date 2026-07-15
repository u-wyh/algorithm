#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define inf 2e9
#define LL long long
#define mod 1000

LL dp[520][520];
LL ans;

int main() {
    int n;
    scanf("%d", &n);

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
    }

    // 动态规划填表
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            for (int k = 1; k < j && j + k <= i; k++) {
                dp[i][j] += dp[i - j][k];
                // 注意：C语言中没有自动类型转换，确保dp[i][j]在累加前是LL类型
                // 但由于dp数组已经是LL类型，这里实际上不需要额外操作
            }
        }
    }

    // 计算结果
    for (int i = 1; i < n; i++) {
        ans += dp[n][i];
        // 注意：累加过程中可能超出int范围，因此使用LL类型
    }

    // 输出结果
    printf("%lld\n", ans);

    return 0;
}
