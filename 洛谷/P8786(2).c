#include <stdio.h>

#define MOD 1000000007

int n, m;
int f[205][105][105];

int main() {
    scanf("%d %d", &n, &m);
    f[0][0][2] = 1; // 初始化条件

    for (int i = 0; i < n + m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k <= m; k++) {
                if (f[i][j][k]) {
                    if (k > 0) {
                        f[i + 1][j + 1][k - 1] = (f[i + 1][j + 1][k - 1] + f[i][j][k]) % MOD;
                    }
                    if (k <= 50) {
                        f[i + 1][j][k * 2] = (f[i + 1][j][k * 2] + f[i][j][k]) % MOD;
                    }
                }
            }
        }
    }

    printf("%d\n", f[n + m][m][0]);
    return 0;
}
