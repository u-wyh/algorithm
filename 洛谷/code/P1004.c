#include <stdio.h>
#include <stdlib.h>

#define MAX_N 15

int N = 0;
int s[MAX_N][MAX_N], f[MAX_N][MAX_N][MAX_N][MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int x, int y, int x2, int y2) {
    if (f[x][y][x2][y2] != -1) return f[x][y][x2][y2];
    if (x == N && y == N && x2 == N && y2 == N) return 0;
    int M = 0;

    // 两种情况同时向下走
    if (x < N && x2 < N) {
        M = max(M, dfs(x + 1, y, x2 + 1, y2) + s[x + 1][y] + s[x2 + 1][y2] - (x + 1 == x2 + 1 && y == y2 ? s[x + 1][y] : 0));
    }

    // 第一种向下，第二种向右
    if (x < N && y2 < N) {
        M = max(M, dfs(x + 1, y, x2, y2 + 1) + s[x + 1][y] + s[x2][y2 + 1] - (x + 1 == x2 && y == y2 + 1 ? s[x + 1][y] : 0));
    }

    // 第一种向右，第二种向下
    if (y < N && x2 < N) {
        M = max(M, dfs(x, y + 1, x2 + 1, y2) + s[x][y + 1] + s[x2 + 1][y2] - (x == x2 + 1 && y + 1 == y2 ? s[x][y + 1] : 0));
    }

    // 两种情况同时向右走
    if (y < N && y2 < N) {
        M = max(M, dfs(x, y + 1, x2, y2 + 1) + s[x][y + 1] + s[x2][y2 + 1] - (x == x2 && y + 1 == y2 + 1 ? s[x][y + 1] : 0));
    }

    f[x][y][x2][y2] = M;
    return M;
}

int main() {
    scanf("%d", &N);
    for (int a = 0; a <= N; a++) {
        for (int b = 0; b <= N; b++) {
            for (int c = 0; c <= N; c++) {
                for (int d = 0; d <= N; d++) {
                    f[a][b][c][d] = -1;
                }
            }
        }
    }

    int t1, t2, t3;
    while (scanf("%d %d %d", &t1, &t2, &t3) && (t1 != 0 || t2 != 0 || t3 != 0)) {
        s[t1][t2] = t3;
    }

    printf("%d\n", dfs(1, 1, 1, 1) + s[1][1]);
    return 0;
}
