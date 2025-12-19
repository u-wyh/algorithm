#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 50
#define L 810

int n, a[N], sum;
double ans = -1.0;
int f[L][L] = {0};

int check(int x, int y, int z) {
    if (x + y > z && x + z > y && y + z > x) return 1;
    return 0;
}

double work(double x, double y, double z) {
    double p = (x + y + z) / 2.0;
    return sqrt(p * (p - x) * (p - y) * (p - z));
}

int main() {
    int i, j, k;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    f[0][0] = 1;

    for (k = 0; k < n; k++) {
        for (i = sum / 2; i >= 0; i--) {
            for (j = sum / 2; j >= 0; j--) {
                if (i - a[k] >= 0 && f[i - a[k]][j]) f[i][j] = 1;
                if (j - a[k] >= 0 && f[i][j - a[k]]) f[i][j] = 1;
            }
        }
    }

    for (i = sum / 2; i > 0; i--) {
        for (j = sum / 2; j > 0; j--) {
            if (!f[i][j]) continue;
            if (!check(i, j, sum - i - j)) continue;
            ans = fmax(ans, work(i, j, sum - i - j));
        }
    }

    if (ans != -1.0) printf("%lld\n", (long long)(ans * 100));
    else printf("%.0f\n", ans);

    return 0;
}
