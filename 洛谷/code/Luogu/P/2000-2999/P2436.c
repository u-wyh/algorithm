#include <stdio.h>
#include <stdlib.h>

// 定义结构体和比较函数用于qsort
typedef struct {
    int x, y;
} sb;

int cmp(const void *a, const void *b) {
    sb *sa = (sb *) a;
    sb *sc = (sb *) b;
    if (sa->x != sc->x)
        return sa->x - sc->x;
    return sa->y - sc->y;
}

int main() {
    int n, m, a[101010], b[101010], c[101010], d[101010], e, f = 0, g, h;
    sb q[101010];

    while (scanf("%d %d", &n,&m) == 2) {
        //scanf("%d", &m);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &b[i]);
        }
        e = (n + m) * 10 + 1;

        for (int i = 2; i <= e; i++) {
            g = 0;
            h = 101010;

            for (int j = 0; j < n; j++) {
                c[j] = a[j] % i;
                if (c[j] == 0) {
                    g = i;
                } else {
                    g = (g > c[j]) ? c[j] : g;
                }
            }

            for (int j = 0; j < m; j++) {
                d[j] = b[j] % i;
                if (d[j] == 0) {
                    h = i;
                } else {
                    h = (h < d[j]) ? d[j] : h;
                }
            }

            if (g < h) {
                q[++f].x = g;
                q[f].y = i - g;
            }
        }

        if (!f) {
            printf("NO\n");
            continue;
        }

        qsort(q + 1, f, sizeof(sb), cmp);

        printf("%d %d\n", q[1].x, q[1].y);
    }

    return 0;
}
