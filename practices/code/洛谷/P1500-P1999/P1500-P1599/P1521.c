// https://www.luogu.com.cn/problem/P1521
// 题意：在 1 到 N 的所有排列中，统计恰有 K 个逆序对的排列个数。
// 逆序对是左侧元素大于右侧元素的一对下标。输出计数对 10000 取模。
// 数据范围：N ≤ 100，0 ≤ K ≤ N(N-1)/2。
// 算法标签：动态规划

#include <stdio.h>

#define MAX_N 5000
#define MAX_K 5000
#define MOD 10000

int N, K;
int f[MAX_N + 1][MAX_K + 1];

int main() {
    scanf("%d %d", &N, &K);

    f[1][0] = 1;
    f[2][1] = 1;
    f[2][0] = 1;
    f[0][0] = 1;

    for (int i = 3; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            f[i][j] = 0;
            for (int k = 0; k <= i - 1 && k <= j; k++) {
                f[i][j] = (f[i][j] + f[i - 1][j - k]) % MOD;
            }
        }
    }

    // 输出结果
    printf("%d\n", f[N][K]);

    return 0;
}
