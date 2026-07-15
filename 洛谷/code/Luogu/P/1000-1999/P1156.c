#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int t, h, l;
} p;

p c[101];
int d, g;
int ti[101];
int f[101];

int cmp(const void *a, const void *b) {
    p *pa = (p *)a;
    p *pb = (p *)b;
    return pa->t - pb->t;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &d, &g);
    for (int i = 0; i < g; i++) {
        scanf("%d %d %d", &c[i].t, &c[i].l, &c[i].h);
    }
    qsort(c, g, sizeof(p), cmp);
    f[0] = 10;

    for (int i = 0; i < g; i++) {
        for (int j = d; j >= 0; j--) {
            if (f[j] >= c[i].t) {
                if (j + c[i].h >= d) {
                    printf("%d\n", c[i].t);
                    return 0;
                }
                f[j + c[i].h] = max(f[j + c[i].h], f[j]);
                f[j] += c[i].l;
            }
        }
    }
    printf("%d\n", f[0]);
    return 0;
}
