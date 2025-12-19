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
