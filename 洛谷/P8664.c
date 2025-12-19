#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h> // For DBL_MAX

#define ll long long
#define N 10000010
#define MOD 1000000007

long double a[N], s, ans, cnt, sum;
ll n;

// 自定义比较函数，用于qsort
int compare(const void *a, const void *b) {
    long double arg1 = *((long double*)a);
    long double arg2 = *((long double*)b);
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main() {
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);

    scanf("%lld %Lf", &n, &s);
    sum = s / n;

    for (ll i = 0; i < n; i++) {
        scanf("%Lf", &a[i]);
    }

    qsort(a, n, sizeof(long double), compare);

    for (ll i = 0; i < n; i++) {
        long double max_take = (i == n - 1) ? a[i] : s / (n - i);
        ans = (max_take < a[i]) ? max_take : a[i];
        s -= ans;
        cnt += (ans - sum) * (ans - sum);
    }

    printf("%.4Lf\n", sqrt(cnt / n));

    return 0;
}
