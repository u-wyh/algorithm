#include <stdio.h>

int n, p;

void solve() {
    scanf("%d%d", &n, &p);
    if (n * 2 < p) {
        for (int i = 1; i <= n; i++) {
            printf("%d ", i);
        }
        printf("\n");
        return;
    }

    for (int i = 1; i * 2 < p; i++) {
        for (int j = 0; j <= n; j += p) {
            if (i + j <= n) printf("%d ", i + j);
            if (j + p - i <= n) printf("%d ", j + p - i);
        }
    }

    for (int i = p; i <= n; i += p) {
        printf("%d ", i);
    }

    if (p % 2 == 0) {
        for (int i = p / 2; i <= n; i += p) {
            printf("%d ", i);
        }
    }

    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
