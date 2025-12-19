#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> // 为了使用INT_MAX

#define MAXN 1005

int n, m;
int a[MAXN][MAXN], f[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(a, 1, sizeof(a));
    int x, y;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        a[x][y] = 0;
    } // 输入

    // 初始化f数组为0，因为动态规划过程中，如果没有树，则不应从该位置开始计算最大正方形边长
    memset(f, 0, sizeof(f));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j]) { // 如果有树
                // 注意，如果i或j为1，则左侧或上方可能没有值，需要单独处理
                int left = (j > 1) ? f[i][j - 1] : 0;
                int up = (i > 1) ? f[i - 1][j] : 0;
                int diag = (i > 1 && j > 1) ? f[i - 1][j - 1] : 0;
                f[i][j] = 1 + min(min(left, up), diag); // 动态转移方程
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans = max(ans, f[i][j]); // ans记录最大值
        }
    }
    printf("%d\n", ans);
    return 0;
}
