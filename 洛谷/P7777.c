#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

ll p, q, n;

void sol() {
    scanf("%lld%lld%lld", &n, &p, &q);
    if (p == 0) {
        printf("0\n");
        return;
    }
    if (n == 1) {
        printf("%lld\n", p);
        return;
    }
    ll x = q / p;
    x = (x - 1) / 2;
    ll res = n - x;
    ll ans = 0;
    if (res % 2) {
        x++;
        res--;
    }
    ans = x * p;
    ans += (x - 1) * x * p / 2;
    ans += (res / 2) * q;
    printf("%lld\n", ans);
}

int main() {
    //freopen("tmp.in", "r", stdin);
    //freopen("tmp.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--) {
        sol();
    }
    return 0;
}
