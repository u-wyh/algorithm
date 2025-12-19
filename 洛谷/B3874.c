#include <stdio.h>

#define N 300005

int n;
int a[N], b[N];
long long ans = 0;

void merge(int l, int r) {
    int mid = l + r >> 1;
    if (l >= r)
        return;
    merge(l, mid);
    merge(mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (a[i] > a[j]) {
            ans += mid - i + 1;
            b[++k] = a[j++];
        } else {
            b[++k] = a[i++];
        }
    }
    while (i <= mid)
        b[++k] = a[i++];
    while (j <= r)
        b[++k] = a[j++];

    for (int i = l; i <= r; i++)
        a[i] = b[i - l + 1];
}

int main() {
    scanf("%d", &n);
    for (int i = n; i; i--) // µ¹Ğò¶ÁÈëÊı¾İ
        scanf("%d", &a[i]);
    merge(1, n);
    printf("%lld", ans);
    return 0;
}
