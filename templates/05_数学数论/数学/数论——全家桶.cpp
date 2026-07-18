// https://www.luogu.com.cn/problem/P2480
//这道题是很多数论知识的结合  很有难度
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define Mod 999911659
#define mod 999911658
#define maxn 40005

long long n, g;
long long d[maxn], tot;
long long p[10], cnt;

inline long long qpow(long long a, long long k, long long p) {
    long long res = 1;
    while (k) {
        if (k & 1) res = (res * a) % p;
        a = (a * a) % p;
        k >>= 1;
    }
    return res % p;
}

long long fac[maxn], inv[maxn];

inline void init(long long p) {
    fac[0] = 1;
    for (register int i = 1; i < p; i++)
        fac[i] = fac[i - 1] * i % p;
    inv[p] = 0;
    inv[p - 1] = qpow(fac[p - 1], p - 2, p);
    for (register int i = p - 2; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % p;
}

inline long long C(long long n, long long m, long long p) {
    if (m > n) return 0;
    return fac[n] * inv[m] % p * inv[n - m] % p;
}

inline long long Lucas(long long n, long long m, long long p) {
    if (m == 0) return 1;
    return Lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}

long long a[10];

inline void calc(int x) {
    init(p[x]);
    for (register int i = 1; i <= tot; i++)
        a[x] = (a[x] + Lucas(n, d[i], p[x])) % p[x];
}

inline long long CRT() {
    long long ans = 0;
    for (register int i = 1; i <= cnt; i++) {
        long long M = mod / p[i];
        long long t = qpow(M, p[i] - 2, p[i]);
        ans = (ans + a[i] % mod * t % mod * M % mod) % mod;
    }
    return (ans + mod) % mod;
}

int main() {
    scanf("%lld%lld", &n, &g);
    if (g % Mod == 0) {
        printf("0\n");
        return 0;
    }
    
    long long t = mod;
    for (register int i = 2; i * i <= mod; i++) {
        if (t % i == 0) {
            p[++cnt] = i;
            while (t % i == 0) t /= i;
        }
    }
    if (t != 1) 
        p[++cnt] = t;

    // for(int i=1;i<=cnt;i++){
    //     cout<<p[i]<<' ';
    // }
    // cout<<endl;
    
    for (register int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            d[++tot] = i;
            if (i * i != n) d[++tot] = n / i;
        }
    }

    // for(int i=1;i<=tot;i++){
    //     cout<<d[i]<<' ';
    // }
    // cout<<endl;
    
    for (register int i = 1; i <= cnt; i++) calc(i);
    
    printf("%lld\n", qpow(g, CRT(), Mod));
    return 0;
}