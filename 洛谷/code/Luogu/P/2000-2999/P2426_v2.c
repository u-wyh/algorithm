#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n, a[110], dp[110][110], ans;

int max(int x, int y) {
    return x > y ? x : y;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int l = n - 1; l > 0; l--) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;

            if (i > 1) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i - 1]);
            }
            if (j < n) {
                dp[i][j] = max(dp[i][j], dp[i][j + 1] + a[j + 1]);
            }

            for (int k = 1; k < i - 1; k++) {
                dp[i][j] = max(dp[i][j], dp[k][j] + abs(a[i - 1] - a[k]) * (i - 1 - k + 1));
            }

            for (int k = j + 2; k <= n; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + abs(a[j + 1] - a[k]) * (k - j));
            }

            ans = max(ans, dp[i][j] + abs(a[j] - a[i]) * (j - i + 1));
        }
    }

    printf("%d\n", ans);
    return 0;
}
