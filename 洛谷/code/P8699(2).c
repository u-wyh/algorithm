#include <stdio.h>
#include <string.h>

#define ll long long
#define MOD 123456

int dp[505][505];

int mod(int a) {
    return a % MOD;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i][0] = 2;
        for (int j = 0; j <= i; j++) {
            dp[i + 1][j] = (dp[i + 1][j] + mod(dp[i][j] * (j + 1))) % MOD;
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + mod(dp[i][j] * 2)) % MOD;
            if (j + 2 <= i) {
                dp[i + 1][j + 2] = (dp[i + 1][j + 2] + mod(dp[i][j] * (i - j - 2))) % MOD;
            }
        }
    }

    printf("%d\n", dp[n][k - 1]);
    return 0;
}
