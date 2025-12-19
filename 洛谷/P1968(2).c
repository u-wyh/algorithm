#include <stdio.h>

// 自定义max函数，因为C标准库中没有
int max(int a, int b) {
    return a > b ? a : b;
}

// 由于需要比较double类型，再实现一个double版本的max
double max_double(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int a[100000];
    double f[10000][2]; // 动态规划数组，存储每天结束时的最大美元和马克价值

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    f[1][0] = 100; // 第一天开始时有100美元
    f[1][1] = a[1]; // 第一天开始时可以全部换成马克

    for (int i = 2; i <= n; i++) {
        // 计算第i天结束时持有美元的最大价值
        f[i][0] = max_double(f[i-1][0], (f[i-1][1] / (double)a[i]) * 100);
        // 计算第i天结束时持有马克的最大价值（以美元表示）
        f[i][1] = max_double(f[i-1][1], f[i-1][0] * a[i] / 100.0);
    }

    // 输出最后一天结束时能获得的最大美元价值
    printf("%.2f\n", max_double(f[n][0], (f[n][1] / (double)a[n]) * 100));

    return 0;
}
