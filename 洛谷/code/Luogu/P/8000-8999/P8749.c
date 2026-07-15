#include <stdio.h>

typedef long long LL;
const LL INF = 1e9;
LL n;

LL C(LL a, LL b) {
    LL res = 1;
    for (LL i = a, j = 1; j <= b; i--, j++) {
        res = res * i / j;
        if (res > n)
            return res;
    }
    return res;
}

int main() {
    scanf("%lld", &n);
    // 只需遍历 16 行
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    for (int i = 16; i >= 0; i--) {
        LL l = 2 * i, r = INF, mid, lim;
        while (l <= r) {
            mid = (l + r) >> 1;
            lim = C(mid, i);
            if (lim == n) {
                printf("%lld\n", (mid + 1) * mid / 2 + i + 1);
                return 0;
            } else if (lim < n)
                l = mid + 1;
            else
                r = mid - 1;
        }
    }
    return 0;
}
