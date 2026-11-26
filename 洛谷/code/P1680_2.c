// https://www.luogu.com.cn/problem/P1680
// 题意：把 N 人分成 M 组，第 i 组人数必须严格大于 C_i。只按每组人数区分方案，求方案数模 10^9+7。
// 数据范围：1 ≤ N,M ≤ 10^6，1 ≤ C_i ≤ 1000，保证有解。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MOD 1000000007
#define MAXN 1000000

typedef long long LL;

int Read() { // 快读
    char c;
    int ans = 0;
    while (!isdigit(c = getchar()));
    do {
        ans = ans * 10 + c - '0';
    } while (isdigit(c = getchar()));
    return ans;
}

int n, m, ans;
int fc[MAXN + 10];

LL Qpow(LL a, LL b) { // 快速幂
    LL ans = 1;
    for (; b; b >>= 1, a = (a * a) % MOD)
        if (b & 1) ans = (ans * a) % MOD;
    return ans;
}

int C(int n, int k) { // 求组合数
    LL fm = (1LL * fc[n - k] * fc[k]) % MOD;
    return (1LL * fc[n] * Qpow(fm, MOD - 2)) % MOD;
}

int main() {
    fc[0] = 1;
    for (int i = 1; i <= MAXN; i++) // 预处理阶乘
        fc[i] = (1LL * fc[i - 1] * i) % MOD;

    n = Read();
    m = Read();
    for (int i = 1; i <= m; i++)
        n -= Read();

    printf("%d\n", C(n - 1, m - 1));
    return 0;
}
