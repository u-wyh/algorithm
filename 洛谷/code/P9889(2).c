#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;
#define N 100000 + 10000
#define M 1000 + 100

ll t;
ll n, m;
ll a[N];
ll b[N];
ll mx;

int check(ll cnt) {
    ll res = 0;
    for (ll i = 1; i <= n; i++) {
        b[i] = cnt / a[i] + (cnt % a[i] != 0);
    }
    for (ll i = 1; i <= n - 1; i++) {
        if (b[i] <= 0) {
            res++; // 直接走到下一个点
            continue;
        }
        res += 2 * b[i] - 1;
        b[i + 1] -= (b[i] - 1);
    }
    if (b[n] > 0) res += 2 * b[n] - 1;
    if (res > m) return 0;
    return 1;
}

int main() {
    scanf("%lld", &t);
    while (t--) {
        mx = 0;
        scanf("%lld %lld", &n, &m);
        for (ll i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            mx = (a[i] > mx) ? a[i] : mx;
        }
        ll l = 0, r = mx * m;
        while (l < r) {
            ll mid = (r + l + 1) / 2;
            if (check(mid)) l = mid;
            else r = mid - 1;
        }
        printf("%lld\n", l);
    }
    return 0;
}
