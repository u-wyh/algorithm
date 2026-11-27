// https://www.luogu.com.cn/problem/P3146
// 题意：输入序列长度 N，以及 N 个正整数。
// 每次操作可以把两个相邻且相等的数合并成一个比原数大 1 的数。
// 不断合并，求最终序列中能出现的最大数值。
// 输出一个整数表示最大数值。
// 数据范围：2 <= N <= 248，初始每个数在 [1, 40] 之间。
#include <stdio.h>
#include <stdlib.h>
// 算法标签：区间动态规划

#define N 250

int f[N][N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, ans = 0;
    scanf("%d", &n);

    // 读取数据并初始化
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f[i][i]);
        ans = max(ans, f[i][i]);
    }

    // 动态规划求解最长公共子序列
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            for (int k = l; k < r; k++) {
                if (f[l][k] == f[k + 1][r] && f[l][k] != 0) { // 注意检查f[l][k]是否为0
                    f[l][r] = max(f[l][r], f[l][k] + 1);
                    ans = max(ans, f[l][r]);
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
