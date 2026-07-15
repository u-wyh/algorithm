#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long LL;
#define maxn 100001

typedef struct {
    int a, b, c;
} node;

node a[maxn];
LL f[maxn], ans;
int T, n, i, j;

int cmp(const void *pa, const void *pb) {
    node *a = (node *)pa;
    node *b = (node *)pb;
    LL product1 = (LL)a->c * b->b;
    LL product2 = (LL)b->c * a->b;
    return (product1 > product2);
}

int main() {
    scanf("%d%d", &T, &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i].a);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i].b);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i].c);

    qsort(a, n, sizeof(node), cmp);

    memset(f, -1, sizeof(f));
    f[0] = 0;

    for (i = 0; i < n; i++) {
        for (j = T; j >= 0; --j) {
            if (f[j] != -1 && j + a[i].c <= T) {
                f[j + a[i].c] = (f[j + a[i].c] > f[j] + (LL)a[i].a - (LL)(j + a[i].c) * (LL)a[i].b) ?
                               f[j + a[i].c] : f[j] + (LL)a[i].a - (LL)(j + a[i].c) * (LL)a[i].b;
            }
        }
    }

    for (i = 0; i <= T; i++)
        if (f[i] > ans)
            ans = f[i];

    printf("%lld\n", ans);
    return 0;
}
