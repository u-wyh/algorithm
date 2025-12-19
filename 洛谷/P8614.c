#include <stdio.h>
#define mod 100000007
typedef long long ll;

int n, s, a, b;
int dp[1007][1007];

int c(int x) {
    return (x % n + n) % n;
}

int main() {
    scanf("%d %d %d %d", &n, &s, &a, &b);
    dp[0][0] = 1;

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dp[i][j] = (dp[i - 1][c(j - a * i)] + dp[i - 1][c(j + b * i)]) % mod;
        }
    }

    printf("%d\n", dp[n - 1][c(s)]);
    return 0;
}
