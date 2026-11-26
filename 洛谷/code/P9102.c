// https://www.luogu.com.cn/problem/P9102
// 题意：有 n 袋糖，第 i 袋有 a_i 颗糖。
// 求有多少个非空袋子子集 S，使得对于任意整数 y in [1, sum_{i in S} a_i]，都能从 S 中选出若干整袋使其糖果总数恰好为 y。
// 答案对 10^9+7 取模。
// 数据范围：1 <= n <= 5000，1 <= a_i <= 5000。
#include <stdio.h>
#include <stdlib.h>

#define N 5010
#define MOD 1000000007

int n, a[N], dp[N], ans;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    dp[0] = 1;

    // 使用qsort对数组a进行排序
    qsort(a + 1, n, sizeof(int), compare);

    for (int i = 1; i <= n; i++) {
        for (int j = N - 10; j >= a[i] - 1; j--) {
            dp[min(j + a[i], N - 10)] = (dp[j] + dp[min(j + a[i], N - 10)]) % MOD;
        }
    }

    for (int i = 1; i <= N - 10; i++) {
        ans = (ans + dp[i]) % MOD;
    }

    printf("%d\n", ans);
    return 0;
}
