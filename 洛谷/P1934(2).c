#include <stdio.h>
#include <stdlib.h>

int n, t;
long long f[1003], s[1003], a[1003];

int main() {
    scanf("%d %d", &n, &t);
    int m = n * n;

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    for (int i = 1; i <= n; i++) {
        long long ans = (long long)m * a[i];
        if (i > 1) {
            ans += f[i - 1];
        }

        for (int j = 1; j < i; j++) {
            if (a[i] + a[j] > t) continue;
            ans = (ans < ((a[i] + a[j]) * (s[i] - s[j - 1]) + f[j - 1])) ? ans : ((a[i] + a[j]) * (s[i] - s[j - 1]) + f[j - 1]);
        }

        f[i] = ans;
    }

    printf("%lld\n", f[n]);
    return 0;
}
