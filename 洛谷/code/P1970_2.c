#include <stdio.h>

#define MAX_N 1000005

int n, h[MAX_N], ans = 1;
int con = 0; // 使用整型代替布尔型

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }

    if (h[2] >= h[1]) {
        con = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (con == 0 && i == n) {
            ans++;
            break;
        }

        if (con == 1) {
            if (h[i + 1] < h[i]) {
                ans++;
                con = 0;
                continue;
            }
        }

        if (con == 0) {
            if (h[i + 1] > h[i]) {
                ans++;
                con = 1;
                continue;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}
