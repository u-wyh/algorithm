#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NR 405
#define MAX_CAPACITY 40005

typedef struct {
    int h, a, c;
} node;

node e[NR];
int n;
bool dp[MAX_CAPACITY];

int cmp(const void *a, const void *b) {
    node *x = (node *)a;
    node *y = (node *)b;
    return x->a - y->a;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &e[i].h, &e[i].a, &e[i].c);
    }
    memset(dp, 0, sizeof(dp));
    dp[0] = true;
    qsort(e, n, sizeof(node), cmp);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < e[i].c; j++) {
            for (int k = e[i].a; k >= e[i].h; k--) {
                dp[k] = dp[k] || dp[k - e[i].h]; // 动态转移方程
            }
        }
    }

    for (int i = e[n-1].a; i >= 0; i--) {
        if (dp[i]) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}
