#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000009
#define MAX_N 1000000

typedef long long ll;

int compare(const void *a, const void *b) {
    ll arg1 = *((ll *)a);
    ll arg2 = *((ll *)b);
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main() {
    ll n, k, a[MAX_N], l, r, ans = 1, b = 1;
    scanf("%lld %lld", &n, &k);

    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    qsort(a, n, sizeof(ll), compare);

    if (k % 2 == 1) {
        ans = (ans * a[n - 1]) % MOD;
        k--;
        n--;
        if (ans < 0) b = -1;
    }

    l = 0;
    r = n - 1;
    k += 2;

    while (k > 0) {
        k -= 2;
        ll left_prod = a[l] * a[l + 1];
        ll right_prod = a[r] * a[r - 1];

        if (left_prod * b >= right_prod * b) {
            ans = (ans * left_prod) % MOD;
            l += 2;
        } else {
            ans = (ans * right_prod) % MOD;
            r -= 2;
        }
    }

    printf("%lld\n", ans % MOD);

    return 0;
}
