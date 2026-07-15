#include <stdio.h>
#include <stdlib.h>

#define MAX_CARS 1000

long long Wb, Sb, n;
long long w[MAX_CARS], v[MAX_CARS], W[MAX_CARS];
double T[MAX_CARS], t[MAX_CARS][MAX_CARS], f[MAX_CARS];

int main() {
    scanf("%lld %lld %lld", &Wb, &Sb, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &w[i], &v[i]);
        T[i] = (double)Sb / v[i] * 60.0;
        t[i][i] = T[i];
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            t[i][j] = (t[i][j - 1] > T[j]) ? t[i][j - 1] : T[j];
        }
    }

    W[0] = 0;
    for (int i = 1; i <= n; i++) {
        W[i] = W[i - 1] + w[i];
    }

    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = T[i] + f[i - 1];
        for (int j = i - 1; j >= 1; j--) {
            if (W[i] - W[j - 1] <= Wb) {
                f[i] = (f[i] < f[j - 1] + t[j][i]) ? f[i] : f[j - 1] + t[j][i];
            } else {
                break;
            }
        }
    }

    printf("%.1lf\n", f[n]);
    return 0;
}
