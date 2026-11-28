// https://www.luogu.com.cn/problem/P10376
// 题意：给初值 n，每轮选择减 a 或减 b。
// 第一次变成不大于 c 时立刻停止，可减成负数。
// 即使 a 等于 b，两种操作也要分别计数。
// 输出：不同操作序列数对 10^9+7 取模。
// 数据范围：1 <= a, b, c <= n <= 2*10^5。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划

#include <stdio.h>

#define MOD 1000000007

int dp[200005];

int main(void)
{
    int n, a, b, c;
    scanf("%d%d%d%d", &n, &a, &b, &c);
    dp[c] = 1;
    for(int i = c + 1; i <= n; ++i){
        int subtract_a = i - a <= c ? 1 : dp[i - a];
        int subtract_b = i - b <= c ? 1 : dp[i - b];
        dp[i] = (subtract_a + subtract_b) % MOD;
    }
    printf("%d\n", dp[n]);
    return 0;
}
