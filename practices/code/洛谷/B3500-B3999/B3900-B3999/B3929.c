// https://www.luogu.com.cn/problem/B3929
// 题意：给门槛 a 和 N 个询问 x。
// 如果 x 是某个不小于 a 的完全平方数的倍数，输出 lucky。
// 否则输出不小于 x 的最小这种数。
// 数据范围：1 ≤ a ≤ 10^6，1 ≤ N ≤ 2 × 10^5，
// 1 ≤ x ≤ 1000001。
// 难度评分：1200（洛谷分级换算）
// 算法标签：筛法、预处理

#include <stdio.h>
#include <math.h>

int a, n;
int b[1002010] = {0};
int la = 1002001;

int main() {
    scanf("%d%d", &a, &n);
    for (int i = (int)ceil(sqrt(a * 1.0)); i * i <= 1002001; i++) {
        for (int j = 1; j * i * i <= 1002001; j++) {
            b[j * i * i] = j * i * i;
        }
    }
    for (int i = 1002000; i >= 1; i--) {
        if (b[i] == i) {
            la = i;
        } else {
            b[i] = la;
        }
    }
    while (n--) {
        int x;
        scanf("%d", &x);
        if (b[x] == x) {
            puts("lucky");
        } else {
            printf("%d\n", b[x]);
        }
    }
    return 0;
}
