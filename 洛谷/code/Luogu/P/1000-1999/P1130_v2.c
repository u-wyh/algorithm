#include <stdio.h>
#include <limits.h> // 用于INT_MAX

#define LL long long

LL n, m;
LL gay[2005][2005];
LL dp[2005][2000];
LL minn = LLONG_MAX; // 使用C语言中的LLONG_MAX表示最大长整型

LL min(LL a, LL b) {
    return a < b ? a : b;
}

int main() {
    scanf("%lld %lld", &n, &m);
    for (LL i = 1; i <= m; i++) {
        for (LL j = 1; j <= n; j++) {
            scanf("%lld", &gay[i][j]); // 注意这里需要%lld来读取long long类型
        }
    }

    // 初始化dp数组，注意这里对于第0个人的处理需要特别小心
    for (LL j = 1; j <= n; j++) {
        dp[0][j-1] = LLONG_MAX; // 初始化为最大值，因为需要从其他状态转移而来
        for (LL i = 1; i <= m; i++) {
            dp[i][j] = LLONG_MAX; // 每个dp状态都初始化为最大值
            // 第i个人做第j步，可以由它的第j-1个步骤的第i-1个人或者第i个人转移过来
            if (j > 1) {
                dp[i][j] = min(dp[i-1][j-1], dp[i][j-1]) + gay[i][j];
            } else {
                dp[i][j] = gay[i][j]; // 如果是第一步，则直接取当前花费
            }
        }
    }

    // 遍历所有可能的最后一步，找到最小值
    for (LL i = 1; i <= m; i++) {
        minn = min(minn, dp[i][n]);
    }

    printf("%lld\n", minn);
    return 0;
}

