#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 30

int dir[8][2] = {{1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1},{0,0}};
int d[MAX_SIZE][MAX_SIZE];
long long dp[MAX_SIZE][MAX_SIZE];
int n, m, cx, cy;

int main() {
    scanf("%d %d %d %d", &n, &m, &cx, &cy);
    d[cx][cy] = 1; // 使用int代替bool
    for (int i = 0; i < 8; i++) {
        int tx = cx + dir[i][0], ty = cy + dir[i][1];
        if (tx >= 0 && tx < n && ty >= 0 && ty < m) {
            d[tx][ty] = 1;
        }
    }
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (!d[i][j]) { // 检查是否不是障碍
                if (i > 0) dp[i][j] += dp[i-1][j];
                if (j > 0) dp[i][j] += dp[i][j-1];
            }
        }
    }
    printf("%lld\n", dp[n][m]);
    return 0;
}
