#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 150001

int n, minn = INT_MAX;
int f[N][3], dp[N][3];

int min(int x, int y) {
    return x < y ? x : y;
}

void solve(int a, int b, int c) {
    memset(dp, INT_MAX, sizeof(dp)); // 默认最大
    dp[1][a] = f[1][a]; // 初值
    for (int i = 2; i <= n; i++) {
        dp[i][a] = dp[i - 1][a] + f[i][a];
        dp[i][b] = min(dp[i - 1][a], dp[i - 1][b]) + f[i][b];
        dp[i][c] = min(dp[i - 1][b], dp[i - 1][c]) + f[i][c];
    }
    minn = min(minn, dp[n][c]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &f[i][0]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &f[i][1]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &f[i][2]);

    solve(0, 1, 2);
    solve(0, 2, 1);
    solve(1, 0, 2);
    solve(1, 2, 0);
    solve(2, 0, 1);
    solve(2, 1, 0);

    printf("%d\n", minn);
    return 0;
}
