#include <stdio.h>
#include <string.h>

#define MAX_N 1001
#define MAX_SUM 100001

int n, maxn, x, g, sum;
int a[MAX_N];
int ans[MAX_SUM];
int f[MAX_SUM];

int main() {
    scanf("%d", &n);
    maxn = 0;
    memset(ans, 0, sizeof(ans));

    for (int k = 1; k <= n; k++) {
        memset(f, 0, sizeof(f));
        g = 0;
        sum = 0;

        while (1) {
            scanf("%d", &x);
            if (x < 0) break;
            a[++g] = x;
            sum += x;
        }

        f[0] = 1;
        a[0] = g;

        if (sum > maxn) maxn = sum;

        for (int i = 1; i <= g; i++) {
            for (int j = sum; j >= a[i]; j--) {
                if (f[j - a[i]] && !f[j]) {
                    f[j] = 1;
                    ans[j]++;
                }
            }
        }
    }

    for (int i = maxn; i >= 0; i--) {
        if (ans[i] == n) {
            printf("%d", i);
            return 0;
        }
    }

    printf("0");
    return 0;
}
