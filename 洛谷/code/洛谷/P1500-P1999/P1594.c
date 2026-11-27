// https://www.luogu.com.cn/problem/P1594
// 题意：按固定排队顺序有 n 辆车过单行桥，不能超车。
// 已知桥最大承重、桥长、每辆车的重量 W 和最快速度 S。
// 车队可分组过桥，同组同时过桥且总重 <= 承重，耗时按组内最慢车算。
// 下一组需等上一组完全过桥后才能上桥，输出最短总时间（分钟，保留 1 位小数）。
// 数据范围：
// n < 1000（车辆总数，为正整数）
// 所有输入数值均在 [1, 10^10] 内
// 算法标签：动态规划、前缀和
#include <stdio.h>
#include <stdlib.h>

#define MAX_CARS 1000

long long Wb, Sb, n;
long long w[MAX_CARS], v[MAX_CARS], W[MAX_CARS];
double T[MAX_CARS], t[MAX_CARS][MAX_CARS], f[MAX_CARS];

int main() {
    scanf("%lld %lld %lld", &Wb, &Sb, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &w[i], &v[i]);
        T[i] = (double)Sb / v[i] * 60.0;
        t[i][i] = T[i];
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            t[i][j] = (t[i][j - 1] > T[j]) ? t[i][j - 1] : T[j];
        }
    }

    W[0] = 0;
    for (int i = 1; i <= n; i++) {
        W[i] = W[i - 1] + w[i];
    }

    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = T[i] + f[i - 1];
        for (int j = i - 1; j >= 1; j--) {
            if (W[i] - W[j - 1] <= Wb) {
                f[i] = (f[i] < f[j - 1] + t[j][i]) ? f[i] : f[j - 1] + t[j][i];
            } else {
                break;
            }
        }
    }

    printf("%.1lf\n", f[n]);
    return 0;
}
