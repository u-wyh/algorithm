#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))

int read() {
    int x = 0, ff = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') ff = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * ff;
}

int f[205][205], a[205];

int main() {
    int n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        f[i][i] = a[i];
    }

    for (int j = 2; j <= n; j++) {
        for (int i = j - 1; i > 0; i--) {
            f[i][j] = abs(a[j] - a[i]) * (j - i + 1);
            for (int k = i; k < j; k++) {
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j]);
            }
        }
    }

    printf("%d\n", f[1][n]);
    return 0;
}
