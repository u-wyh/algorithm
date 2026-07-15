#include <stdio.h>

#define MOD 1000000007

int n, c;
int dp[10004], s[10004];

int main() {
    scanf("%d %d", &n, &c);
    dp[0] = 1;

    for (int i = 2; i <= n; i++) {
        s[0] = dp[0];
        for (int j = 1; j <= c; j++) {
            s[j] = (s[j - 1] + dp[j]) % MOD;
        }

        for (int j = 0; j <= c; j++) {
            if (j >= i) {
                dp[j] = (s[j] - s[j - i] + MOD) % MOD;
            } else {
                dp[j] = s[j];
            }
        }
    }

    printf("%d\n", dp[c]);
    return 0;
}
