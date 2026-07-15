#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

long long n, m, a[MAXN], b[MAXN], ans;

int compare(const void *x, const void *y) {
    long long x_val = *(long long *)x;
    long long y_val = *(long long *)y;
    return (x_val < y_val) ? -1 : (x_val > y_val);
}

int check(long long k) {
    long long l = 0, r = m - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (k < b[mid]) r = mid - 1;
        else if (k > b[mid]) l = mid + 1;
        else return 1;
    }
    return 0;
}

int main() {
    scanf("%lld %lld", &n, &m);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i < m; i++) scanf("%lld", &b[i]);

    // 注意这里要对b数组的m个元素进行排序，而不是m+1个
    qsort(b, m, sizeof(long long), compare);

    // 初始判断最后一个元素
    if (!check(a[n - 1])) ans++;

    // 遍历数组a，除了最后一个元素
    for (int i = 0; i < n - 1; i++) {
        if (!check(a[i]) && check(a[i + 1])) ans++;
    }

    printf("%lld\n", ans);
    return 0;
}
