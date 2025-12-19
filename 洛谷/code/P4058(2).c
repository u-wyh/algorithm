#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 200001

typedef unsigned long long ull;
typedef long long ll;

ull n, s, l;
ull h[MAXN], a[MAXN];

int read() {
    int x = 0, c = 1;
    char ch = ' ';
    while ((ch > '9' || ch < '0') && ch != '-') ch = getchar();
    if (ch == '-') c = -1, ch = getchar();
    while (ch <= '9' && ch >= '0') x = x * 10 + ch - '0', ch = getchar();
    return x * c;
}

bool check(ll x) {
    ull cnt = 0;
    for (int i = 0; i < n; i++) {
        if (h[i] + a[i] * x >= l) {
            cnt += h[i] + a[i] * x;
            if (cnt >= s) break;
        }
    }
    return cnt >= s;
}

int main() {
    scanf("%llu %llu %llu", &n, &s, &l);
    for (int i = 0; i < n; i++) h[i] = read();
    for (int i = 0; i < n; i++) a[i] = read();

    ll left = 0, right = 100000000000000000ll;
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (check(mid)) right = mid - 1;
        else left = mid + 1;
    }

    printf("%lld\n", left);
    return 0;
}
