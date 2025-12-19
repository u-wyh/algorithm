#include <stdio.h>

#define LL long long
#define mod 998244353

int n;
LL Ans;

LL read() {
    LL x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

LL qu_pow(LL a, LL k) {
    LL ans = 1, base = a;
    while (k) {
        if (k & 1) ans = (ans * base) % mod;
        base = (base * base) % mod;
        k >>= 1;
    }
    return ans;
}

int main() {
    n = read();
    LL fact = 1;
    for (int i = 2; i <= n; i++) {
        fact = (fact * i) % mod;
    }

    for (int i = 1; i < n; i++) {
        LL sum = 0;
        for (int j = 1; j <= n - i + 1; j++) {
            sum = (sum + read()) % mod;
        }
        sum = (sum * qu_pow(n - i + 1, mod - 2)) % mod; // 求解每一行的平均值
        Ans = (Ans + sum) % mod;
    }

    Ans = (Ans * fact) % mod; // 最后乘排列数
    printf("%lld\n", Ans);
    return 0;
}
