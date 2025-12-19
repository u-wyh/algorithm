#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long
#define MODE 10000

ll dp[1005][1005];
ll s[1005][1005];//表示前缀和
ll n, k;

int main() {
    scanf("%lld %lld", &n, &k);
    dp[1][0] = 1;
    for (int i = 0; i <= k; i++) {
        s[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= (n * (n - 1) / 2) && j <= k; j++) {
            if (j - i < 0) {
                dp[i][j] = s[i - 1][j];
            } else {
                dp[i][j] = (s[i - 1][j] - s[i - 1][j - i] + MODE) % MODE;
            }
        }

        s[i][0] = dp[i][0];
        for (int j = 1; j <= k; j++) {
            s[i][j] = (s[i][j - 1] + dp[i][j]) % MODE;
        }
    }

    printf("%lld\n", dp[n][k]);
    return 0;
}
