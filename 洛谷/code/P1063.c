// https://www.luogu.com.cn/problem/P1063
// 题意：有 N 颗珠子围成一圈，每颗珠子的尾标记就是后一颗的头标记。
// 合并相邻两珠时，保留最外侧两个标记，释放这两个标记与中间共有标记的乘积。
// 求一直合并到只剩一颗时的最大总能量。
// 数据范围：4 ≤ N ≤ 100，头标记在 [1,1000]，答案不超过 2.1 × 10^9。
// 算法标签：区间动态规划

#include <stdio.h>
#include <stdlib.h>

#define FOR(i, n, m) for (int i = n; i <= m; i++)

int f[210][210], a[420]; // 数组a的大小加倍以存储复制的数据
int n, ans = 0;

int main() {
    scanf("%d", &n);
    FOR(i, 1, n) scanf("%d", &a[i]);
    FOR(i, n + 1, 2 * n) a[i] = a[i - n]; // 复制数组a

    // 初始化f数组（可选，但在这个问题中，由于我们是通过比较来更新f的，所以不需要显式初始化）

    // 动态规划填表
    FOR(i, 2, n) {
        FOR(j, 1, 2 * n - i) {
            FOR(k, j, j + i - 2) {
                f[j][j + i - 1] = (f[j][k] + f[k + 1][j + i - 1] + a[j] * a[j + i] * a[k + 1] > f[j][j + i - 1]) ?
                                  f[j][k] + f[k + 1][j + i - 1] + a[j] * a[j + i] * a[k + 1] :
                                  f[j][j + i - 1];
            }
        }
    }

    // 查找最大值
    FOR(i, 1, n) {
        if (f[i][n + i - 1] > ans) {
            ans = f[i][n + i - 1];
        }
    }

    printf("%d\n", ans);
    return 0;
}
