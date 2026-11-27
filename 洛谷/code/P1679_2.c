// https://www.luogu.com.cn/problem/P1679
// 题意：输入一个正整数 m。
// 将 m 分解为 n 个正整数的四次方之和，输出所需的最小项数 n。
// 数据范围：
// m <= 100,000（待分解的整数）
#include <stdio.h>
#include <limits.h>
// 算法标签：动态规划、完全背包

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
