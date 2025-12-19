#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 1000010

typedef long long ll;

int n, m;
int a[MAXN], b[MAXN];
ll t[MAXN];
bool v[MAXN];

int compare(const void *a, const void *b) {
     return (*(int*)a - *(int*)b);
}
bool check(ll x) {
    ll s = 0;
    int i, j = 1, k = 0;
    for (i = 1; i <= n; i++) {
        while (k > 0 && i - b[j] >= x) {
            s -= k;
            k--;
            j++;
        }
        if (v[i]) {
            k++;
            s += x;
        }
        t[i] = s;
    }

    s = 0;
    int p = m;
    for (i = n; i > 0; i--) {
        while (k > 0 && b[p] - i >= x) {
            s -= k;
            k--;
            p--;
        }
        if (v[i]) {
            k++;
            s += x;
            t[i] -= x;
        }
        t[i] += s;
    }

    for (i = 1; i <= n; i++) {
        if (t[i] < a[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
        v[b[i]] = true;
    }
    qsort(b + 1, m, sizeof(int), compare); // 注意：这里使用qsort，且需要合适的比较函数

    ll l = 0, r = 1e9 + n;
    while (l < r) {
        ll mid = l + (r - l) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%lld\n", l);
    return 0;
}

// int compare(const void *a, const void *b) {
//     return (*(int*)a - *(int*)b);
// }
// 然后在qsort中调用它：qsort(b + 1, m, sizeof(int), compare);
