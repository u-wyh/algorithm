#include <stdio.h>

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int a[105], dp[1000005] = {0};

int main() {
    int n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }
    int t = a[1];
    for (int i = 2; i <= n; i++) {
        t = gcd(t, a[i]);
    }
    if (t > 1) { // 无限解
        printf("INF\n");
        return 0;
    }
    // 有限不超过N^2
    dp[0] = 1;
    for (int i = 0; i <= 1000000; i++) {
        if (dp[i]) {
            for (int j = 1; j <= n; j++) {
                dp[i + a[j]] = 1;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= 1000000; i++) {
        if (!dp[i]) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
