#include <stdio.h>

#define MOD 19650827

int f[2010][2010][2], a[2010];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 初始化长度为1的子序列
    for (int i = 1; i <= n; i++) {
        f[i][i][0] = 1;
    }

    // 动态规划计算子序列个数
    for (int len = 1; len <= n; len++) {
        for (int i = 1, j = i + len; j <= n; i++, j++) {
            if (a[i] < a[i + 1]) {
                f[i][j][0] = (f[i][j][0] + f[i + 1][j][0]) % MOD;
            }
            if (a[i] < a[j]) {
                f[i][j][0] = (f[i][j][0] + f[i + 1][j][1]) % MOD;
            }
            if (a[j] > a[i]) {
                f[i][j][1] = (f[i][j][1] + f[i][j - 1][0]) % MOD;
            }
            if (a[j] > a[j - 1]) {
                f[i][j][1] = (f[i][j][1] + f[i][j - 1][1]) % MOD;
            }
        }
    }

    // 输出结果
    printf("%d\n", (f[1][n][0] + f[1][n][1]) % MOD);

    return 0;
}
