// https://www.luogu.com.cn/problem/P2946
// 题意：输入奶牛数 N、幸运数字 F，以及每头奶牛的能力值 R_i。
// 从这 N 头奶牛中选出至少 1 头组成一支队伍，
// 要求所有队员的能力值总和恰好是 F 的倍数。
// 统计满足要求的非空队伍组合方案数。
// 输出一个整数，表示方案数对 10^8 取模的值。
// 数据范围：对于 100% 的数据，1 <= N <= 2000，
// 1 <= F <= 1000，1 <= R_i <= 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划、背包动态规划
#include <stdio.h>
#include <stdlib.h>

#define p 100000000 // 定义常数
#define N 2010
#define F 1010

int n, f;
int r[N];
long long h[N][F];

int main() {
    int i, j;
    scanf("%d %d", &n, &f);
    for (i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
        r[i] %= f; // 提前取模
    }

    // 初始化
    for (i = 1; i <= n; i++) {
        h[i][r[i]] = 1;
    }

    // 动态规划计算
    for (i = 1; i <= n; i++) {
        for (j = 0; j < f; j++) {
            h[i][j] = (h[i][j] + h[i-1][j]) % p;
            h[i][j] = (h[i][j] + h[i-1][(j - r[i] + f) % f]) % p; // 每加一次就%p
        }
    }
    printf("%lld\n", h[n][0]);
    return 0;
}
