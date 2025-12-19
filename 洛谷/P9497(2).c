#include <stdio.h>
#include <stdlib.h>

#define N 1000005

int n, q;
int cnt = 0;
int a[N];

// 自定义比较函数，用于qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


void solve(int v) {
    int l = n * (n - 1) + 1;
    int r = n * n;
    if (v <= a[l]) {
        printf("%d\n", n);
        return;
    }
    if (v > a[r]) {
        printf("0\n");
        return;
    }
    int mid;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (v <= a[mid])
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", n * n + 1 - l);
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int num;
            scanf("%d", &num);
            a[++cnt] = num;
        }
    }
    qsort(a + 1, cnt, sizeof(int), (int (*)(const void *, const void *))compare);

    while (q--) {
        int v;
        scanf("%d", &v);
        solve(v);
    }
    return 0;
}
