#include <stdio.h>

#define MOD 1000000007

long long s[200005];

int main() {
    int n, a, b, c;
    long long ans = 0;
    scanf("%d %d %d %d", &n, &a, &b, &c);

    if (n == c) { // льеп
        printf("1\n");
        return 0;
    }

    s[n] = 1;
    for (int i = n; i > c; i--) {
        if (i - a > c) {
            s[i - a] = (s[i - a] + s[i]) % MOD;
        } else {
            ans = (ans + s[i]) % MOD;
        }

        if (i - b > c) {
            s[i - b] = (s[i - b] + s[i]) % MOD;
        } else {
            ans = (ans + s[i]) % MOD;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
