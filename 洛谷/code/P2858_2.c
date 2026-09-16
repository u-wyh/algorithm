#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2010

int max(int a, int b) {
    return (a > b) ? a : b;
}

int n, f[MAX_N][MAX_N], v[MAX_N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }

    // 初始化动态规划数组，可以全部设为0，但在这个问题中，由于我们总是取最大值，所以初始值不影响结果

    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= i; j--) {
            int a = n - (j - i + 1); // 计算剩余天数
            f[i][j] = max(f[i - 1][j] + v[i - 1] * a, f[i][j + 1] + v[j + 1] * a); // 转移方程
        }
    }

    int maxn = 0;
    for (int i = 1; i <= n; i++) {
        maxn = max(maxn, f[i][i] + v[i] * n); // 加上最后一天卖出的价格
    }

    printf("%d\n", maxn);

    return 0;
}
