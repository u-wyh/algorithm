#include <stdio.h>
#include <limits.h>

#define MAXN 100005

int m, dp[MAXN];

// 自定义的min函数
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        dp[i] = INT_MAX; // 使用INT_MAX代替1e9+7，因为C标准库中没有直接的1e9+7常量
    }
    dp[1] = 1;

    for (int i = 2; i <= m; i++) {
        for (int j = 1; j * j * j * j <= i; j++) {
            dp[i] = min(dp[i], dp[i - (j * j * j * j)] + 1);
        }
    }

    printf("%d\n", dp[m]);
    return 0;
}
