// https://www.luogu.com.cn/problem/P8774
// 题意：输入正整数 n 和 n 行整数 x_i,
// y_i（表示从高度 i-1 爬到高度 i
// 有概率 P_i = x_i / y_i 掉回高度 0
// 成功爬一格耗时 1，掉落那次尝试也耗费时间 1）；
// 输出从高度 0 爬到高度 n 的期望时间对 998244353 取模的结果。
// 数据范围：1 <= n <= 10^5，
// 1 <= x_i < y_i <= 10^9。
// 难度评分：1500（洛谷分级换算）
// 算法标签：概率与期望、快速幂、乘法逆元
#include <stdio.h>

#define N 100005
#define P 998244353

int n, a[N], b[N];

// 快速幂函数
int fp(int x, int y) {
    int res = 1;
    for (; y; y >>= 1) {
        if (y & 1) res = (res * 1LL * x) % P;
        x = (x * 1LL * x) % P;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);

    int s1 = 1, s2 = 0, s3 = 0;
    for (int i = 1; i <= n; i++) {
        // 使用费马小定理计算概率
        int p1 = (a[i] * 1LL * fp(b[i], P - 2)) % P;
        int p2 = ((b[i] - a[i]) * 1LL * fp(b[i], P - 2)) % P;

        s3 = (s3 + s1) % P; // 计算系数
        s2 = (s2 + 1LL * s1 * p1) % P;
        s1 = (s1 * 1LL * p2) % P;
    }

    // 输出最终结果
    printf("%d\n", (1LL * s3 * fp(1 - s2 + P, P - 2)) % P);
    return 0;
}
