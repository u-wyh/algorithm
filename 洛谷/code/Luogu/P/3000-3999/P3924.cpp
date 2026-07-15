#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 1e7 + 5;
ll sumv[maxn << 1], a[maxn], s[maxn];
int p[maxn];

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline void write(ll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

#define lson o<<1
#define rson o<<1|1
int d = 0;//统计最大深度

void build(int l, int r, int o, int t) {
    if (l == r) {
        sumv[o] = a[l];
        p[l] = t;
        d = max(d, t);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lson, t + 1);
    build(mid + 1, r, rson, t + 1);
    sumv[o] = sumv[lson] + sumv[rson];
}

ll query(int l, int r, int o, int t, ll tt) {
    if (l == r) {
        return (1LL << t) * (tt + sumv[o]);
    }
    int mid = (l + r) >> 1;
    return query(l, mid, lson, t - 1, tt + sumv[o]) + 
           query(mid + 1, r, rson, t - 1, tt + sumv[o]);
}

ll gcd(ll a, ll b) {
    while (b) {
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    int n = read(), m = read(), yyy = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
    }
    
    build(1, n, 1, 1);
    ll ans = query(1, n, 1, d - 1, 0);
    ll y = 1LL << (d - 1);
    ll yy = gcd(y, yyy);
    yyy /= yy;
    y /= yy;
    
    for (int i = 1; i <= n; ++i) {
        s[i] = s[i - 1] + (((1LL << p[i]) - 1) << (d - p[i]));
    }
    
    while (m--) {
        int l = read(), r = read(), x = read();
        ans += (s[r] - s[l - 1]) * x;
        write(ans / y * yyy);
        putchar('\n');
    }
    
    return 0;
}