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
