// https://www.luogu.com.cn/problem/P1387
// 题意：给一个 01 矩阵，在里面找每个格子都是 1 的最大连续正方形，输出其边长。
// 数据范围：1 ≤ n,m ≤ 100，保证至少有一个 1。

#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int a[101][101], n, m, f[101][101], ans = 0;

int main()
{
    scanf("%d %d", &n, &m); // 读入
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            // 因为只需用到i, j上方，左方，左上方的信息，读入同步处理
            // 注意：初始时f[i][j]需要初始化，否则可能包含未定义的值
            if (i == 1 || j == 1) {
                f[i][j] = a[i][j]; // 边界情况，第一个元素直接赋值
            } else if (a[i][j] == 1) {
                f[i][j] = min(min(f[i][j-1], f[i-1][j]), f[i-1][j-1] ) + 1;
                // 注意：当i或j为1时，f[i-1][j-1]是未定义的，因此需要检查i和j是否大于1
            }
            ans = max(ans, f[i][j]); // 同步更新答案
        }
    }
    printf("%d", ans);
    return 0;
}
