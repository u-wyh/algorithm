// https://www.luogu.com.cn/problem/P3399
// 题意：输入城市段数 N、总天数上限 M，各段距离 D_1..D_N，
// 以及第 1..M 天的天气恶劣值 C_1..C_M。
// 从 0 号城市出发，
// 每天可休息（疲劳 0）或从 i-1 走到 i（疲劳 D_i * C_j），
// 要求在不超过 M 天内到达 N 号城市。
// 输出最小总疲劳度。
// 数据范围：1 <= N <= M <= 1000，
// 1 <= D_i, C_i <= 1000。
// 算法标签：动态规划
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 2139063143
#define MAX_N 1002
#define MAX_M 1002

int D[MAX_N], C[MAX_M], f[MAX_N][MAX_M];

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 1; i <= M; i++) {
        scanf("%d", &C[i]);
    }
    memset(f, 0x7f, sizeof(f));
    for (int i = 0; i <= M; i++) {
        f[0][i] = 0;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= M; j++) {
            f[i][j] = (f[i][j-1] < f[i-1][j-1] + D[i] * C[j]) ? f[i][j-1] : f[i-1][j-1] + D[i] * C[j];
        }
    }
    int ans = INF;
    for (int i = N; i <= M; i++) {
        ans = (ans < f[N][i]) ? ans : f[N][i];
    }
    printf("%d\n", ans);
    return 0;
}
