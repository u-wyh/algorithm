#include <stdio.h>
#include <string.h>

int f[11][16], graph[11][16], path[11][16][11], n, m;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= j; k++) {
                if (f[i][j] < f[i - 1][k] + graph[i][j - k]) {
                    f[i][j] = f[i - 1][k] + graph[i][j - k];
                    for (int h = 1; h < i; h++) {
                        path[i][j][h] = path[i - 1][k][h];
                    }
                    path[i][j][i] = j - k; // 因为改为了“不给”第i家公司k台机器，所以必须如此调整
                }
            }
        }
    }
    printf("%d\n", f[n][m]);
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", i, path[n][m][i]);
    }
    return 0;
}
