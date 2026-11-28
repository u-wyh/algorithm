// https://www.luogu.com.cn/problem/P6883
// 题意：N 个装水的杯子，将 i 号杯的水倒入 j 号杯需代价 C_{i,j}，
// 求倒水使得至多有 K 个杯子中有水的最小总代价。
// 数据范围：1 <= K <= N <= 20，
// 0 <= C_{i,j} <= 10^5，C_{i,i} = 0。
// 难度评分：1700（洛谷分级换算）
// 算法标签：状态压缩动态规划
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 21

int n, m, a[N][N], dp[1 << N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) { // 判断第j位是不是1
                for (int k = 0; k < n; k++) {
                    if (!(i & (1 << k))) { // 判断第k位是不是0
                        dp[i] = (dp[i] < dp[i ^ (1 << j)] + a[j][k]) ? dp[i] : dp[i ^ (1 << j)] + a[j][k];
                    }
                }
            }
        }
    }

    int ans = INT_MAX; // 即INT_MAX，表示最大整数
    for (int i = 0; i < (1 << n); i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (!(i & (1 << j))) cnt++; // 统计有几位是0
        }
        if (cnt <= m) ans = (ans < dp[i]) ? ans : dp[i];
    }

    printf("%d\n", ans);
    return 0;
}
