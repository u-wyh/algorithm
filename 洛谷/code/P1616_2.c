// https://www.luogu.com.cn/problem/P1616
// 题意：输入总采药时间 t 和草药种类数 m，及每种草药的采摘时间 a_i 与价值 b_i。
// 每种草药可无限次采摘（完全背包），输出总时间不超过 t 时能获得的最大价值。
// 数据范围：
// 1 <= m <= 10^4（草药种类数）
// 1 <= t <= 10^7（总时间）
// 1 <= m*t <= 10^7
// 1 <= a_i, b_i <= 10^4（每种草药耗时与价值）
#include <stdio.h>
#include <stdlib.h>

#define LL long long
#define N 10000005

LL f[N];
LL w, c, n, m;

int main() {
    int i;
    scanf("%lld %lld", &m, &n);  // 读取m和n

    // 初始化f数组为0（可选，如果数组在全局作用域定义，则自动初始化为0）
    for (i = 0; i <= m; i++) {
        f[i] = 0;
    }

    while (n--) {
        scanf("%lld %lld", &w, &c);  // 读取w和c
        for (i = w; i <= m; i++) {
            f[i] = (f[i] > f[i - w] + c) ? f[i] : f[i - w] + c;
        }
    }

    printf("%lld\n", f[m]);  // 输出f[m]

    return 0;
}
