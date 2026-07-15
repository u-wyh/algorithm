#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t, val;
} ben;

ben a[505];
int vis[505];

// 比较函数，用于qsort
int cmp(const void *a, const void *b) {
    ben *x = (ben *)a;
    ben *y = (ben *)b;
    return y->val - x->val; // 降序排序
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i].t);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i].val);
    }

    // 使用qsort进行排序
    qsort(a, n, sizeof(ben), cmp);

    int ans = 0, t = 0;
    for (int i = 0; i < n; i++) {
        int tag = 0;
        for (int j = a[i].t; j > 0; j--) {
            if (vis[j] == 0) {
                vis[j] = 1;
                tag = 1;
                break;
            }
        }
        if (tag == 0) {
            ans += a[i].val;
        }
    }

    printf("%d\n", m - ans);
    return 0;
}
