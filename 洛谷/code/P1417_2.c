// https://www.luogu.com.cn/problem/P1417
// 题意：有 n 种食材和总时间 T，可任选一部分并安排烹调顺序。第 i 种耗时 c[i]，若在时刻 t 做完，贡献 a[i]-t×b[i]。求在时限内的最大总美味值。
// 数据范围：1 ≤ n ≤ 50，所有输入数均小于 10^5。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LL long long
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
    LL prod1 = (LL)a->c * (LL)b->b;
    LL prod2 = (LL)b->c * (LL)a->b;
    if (prod1 < prod2) return -1;
    if (prod1 > prod2) return 1;
    return 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

LL max_ll(LL a, LL b) {
    return (a > b) ? a : b;
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

    memset(f, 0, sizeof(f));
    //f[0] = 0;
    /*
    for (i = 0; i < n; i++) {
        for (j = T; j >= 0; --j) {
            if (f[j] != -1 && j + a[i].c <= T) {
                f[j + a[i].c] = max_ll(f[j + a[i].c], f[j] + (LL)a[i].a - (LL)(j + a[i].c) * (LL)a[i].b);
            }
        }
    }

    事实上  我更倾向于下面一种*/
    for (i = 0; i < n; i++) {
        for (j = T; j >= a[i].c; j--) {
            f[j]=max_ll(f[j],f[j-a[i].c]+a[i].a-j*a[i].b);
        }
    }

    for (i = 0; i <= T; i++)
        ans = max_ll(ans, f[i]);
    printf("%lld\n", ans);
    return 0;
}
