#include <stdio.h>
#include <stdlib.h>

#define MAX_N 55

int n, i, j, l, k, x, y, s;
int d[MAX_N][MAX_N], f[MAX_N][MAX_N][MAX_N][MAX_N];

int max(int a,int b)
{
    return a>b?a:b;
}
int main() {
    scanf("%d", &n);
    while (scanf("%d %d %d", &x, &y, &s) && x) {
        d[x][y] = s;
    }

    // 初始化dp数组，这里假设初始化为0，如果有特定的初始值需求请修改
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++) {
            for (l = 0; l <= n; l++) {
                for (k = 0; k <= n; k++) {
                    f[i][j][l][k] = 0;
                }
            }
        }
    }

    // 动态规划计算
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            for (l = 1; l <= n; l++) {
                for (k = 1; k <= n; k++) {
                    f[i][j][l][k] = max(max(f[i - 1][j][l - 1][k], f[i][j - 1][l][k - 1]),
                                       max(f[i - 1][j][l][k - 1], f[i][j - 1][l - 1][k])) + d[i][j];
                    if (i != l && j != k) {
                        f[i][j][l][k] += d[l][k];
                    }
                }
            }
        }
    }

    printf("%d\n", f[n][n][n][n]);
    return 0;
}

