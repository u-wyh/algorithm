// https://www.luogu.com.cn/problem/P1775
// 题意：把排成一行的 N 堆石子合为一堆。每次只能合并相邻两堆，费用等于两堆质量之和，求最小总费用。
// 数据范围：N ≤ 300，每堆质量 m_i ≤ 1000。

#include <stdio.h>
#include <limits.h>

#define MAX_N 1005

int a[MAX_N], f[MAX_N][MAX_N], n;

int dfs(int l, int r) {
    if (l == r) return 0; // 自己与自己合并，代价为0
    if (f[l][r] != INT_MAX) return f[l][r]; // 记忆化，已经求解的直接返回
    int min_cost = INT_MAX;
    for (int i = l; i < r; ++i) {
        int cost = dfs(l, i) + dfs(i + 1, r) + a[r] - a[l - 1];
        min_cost = (cost < min_cost) ? cost : min_cost;
    }
    f[l][r] = min_cost;
    return min_cost;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            f[i][j] = INT_MAX;
        }
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] += a[i - 1]; // 前缀和
    }
    printf("%d\n", dfs(1, n));
    return 0;
}
