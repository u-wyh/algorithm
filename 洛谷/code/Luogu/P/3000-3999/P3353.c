#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000005

int f[MAX_N], sum[MAX_N], n, m, x, y, ans, maxn;

int read() {
    int x = 0;
    char c;
    int f = 0; // 0 for positive, 1 for negative

    c = getchar();
    if (c == '-') f = 1;
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
    return x;
}

typedef struct {
    int x, y;
} mmp;

int cmp(const void *a, const void *b) {
    mmp *m1 = (mmp *)a;
    mmp *m2 = (mmp *)b;
    return m1->x - m2->x;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    n = read();
    m = read();
    maxn = 1;
    for (int i = 0; i < n; i++) {
        x = read();
        y = read();
        f[x] += y;
        maxn = max(maxn, x);
    }

    for (int i = 1; i <= maxn; i++) {
        sum[i] = sum[i - 1] + f[i];
    }

    ans = -1;
    for (int i = m; i <= maxn; i++) {
        ans = max(ans, sum[i] - sum[i - m]);
    }

    printf("%d\n", ans);
    return 0;
}
