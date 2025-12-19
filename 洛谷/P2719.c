#include <stdio.h>

#define M 1500

int n;
double f[M][M];

int main() {
    scanf("%d", &n);
    n >>= 1; // 将n除以2并取整

    // 初始化边界条件
    for (int i = 2; i <= n; i++) {
        f[i][0] = 1.0;
        f[0][i] = 1.0;
    }
    //f[i][j]的含义是售票员手中有i张a   j张b时   最后两张一样的概率

    // 动态规划计算f[i][j]
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++) {
            f[i][k] = f[i-1][k] * 0.5 + f[i][k-1] * 0.5;
        }
    }

    // 输出结果，保留四位小数
    printf("%.4lf\n", f[n][n]);

    return 0;
}
