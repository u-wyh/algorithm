#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} lin;

int cmp(const void *x, const void *y) {
    lin *x1 = (lin *)x;
    lin *x2 = (lin *)y;
    return x1->a - x2->a;
}

int main() {
    int i, N, C, lin1 = 0, sum = 0;
    scanf("%d %d", &N, &C);
    lin s[30];
    for (i = 0; i < N; i++) {
        int l1, l2;
        scanf("%d %d", &l1, &l2);
        if (l1 >= C) sum += l2;
        else {
            s[lin1].a = l1;
            s[lin1].b = l2;
            lin1++;
        }
    }

    qsort(s, lin1, sizeof(s[0]), cmp);

    while (1) {
        int x = C;
        for (i = lin1 - 1; i >= 0; i--) {
            if (s[i].b > 0 && x >= s[i].a) {
                int count = x / s[i].a;
                if (count > s[i].b) count = s[i].b;
                x -= count * s[i].a;
                s[i].b -= count;
            }
        }

        if (x > 0) {
            for (i = 0; i < lin1; i++) {
                if (s[i].b > 0 && x <= s[i].a) {
                    x -= s[i].a;
                    s[i].b--;
                    break;
                }
            }
        }

        if (x > 0) break;
        sum++;
    }

    printf("%d\n", sum);
    return 0;
}
