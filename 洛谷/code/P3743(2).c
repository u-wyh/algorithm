#include <stdio.h>

int n; // 设备数量
double p; // 充电器的充电速度
double a[200000], b[200000];
double lbound = 0, rbound = 1e10;
double sum = 0; // 需要的能量总和（验证答案时）、所有设备的消耗能量速度总和（-1特判时）

int check(double ans) { // 验证答案
    double q = p * ans; // 充电器最多提供的能量
    sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] * ans <= b[i]) { // 若设备已有的能量大于使用时间需要的能量
            continue; // 忽略该设备
        }
        sum += (a[i] * ans - b[i]); // 否则用充电器充电，使设备已有的能量等于使用时间需要的能量，并记录需要的能量。
    }
    return sum <= q; // 最后比较需要的能量总和和充电器最多提供的能量。
}

int main() {
    scanf("%d %lf", &n, &p);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &a[i], &b[i]);
        sum += a[i];
    }
    if (sum <= p) { // 若所有设备的消耗能量速度总和还是小于充电器的充电速度，输出-1。
        printf("%.6f\n", -1.0);
        return 0;
    }
    while (rbound - lbound > 1e-6) {
        double mid = (lbound + rbound) / 2;
        if (check(mid)) {
            lbound = mid;
        } else {
            rbound = mid;
        }
    }
    printf("%.6f\n", lbound);
    return 0;
}
