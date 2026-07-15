#include <stdio.h>

int i, j, k, m, n, ans = 2, a[10001], b[10001];

void checkx() {
    for (i = 2; i <= n + 1; i++) {
        b[i] = a[i - 1] - b[i - 1] - b[i - 2];
        if (b[i] != 1 && b[i] != 0) {
            ans--;
            break;
        }
        if (i == n + 1 && b[i] != 0) {
            ans--;
            break;
        }
    }
}

int main() {
    scanf("%d", &n);
    b[0] = 0;
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    b[1] = 1;
    checkx();
    b[1] = 0;
    checkx();
    printf("%d\n", ans);
    return 0;
}
