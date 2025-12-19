#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 11

long long a[MAX_N][MAX_N];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int tx, ty, lx, ly, n, m, mou = 6, times = 0, minans = INT_MAX;

void dfs(int x, int y, int mou) {
    if (mou == 0 || times > n * m || times >= minans) return;

    if (a[x][y] == 4) mou = 6;
    if (x == lx && y == ly) minans = (times < minans) ? times : minans;
    else {
        for (int i = 0; i < 4; i++) {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];
            if (nx <= 0 || nx > n || ny <= 0 || ny > m || a[nx][ny] == 0) continue;

            times++;
            dfs(nx, ny, mou - 1);
            times--;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
            if (a[i][j] == 2) {
                tx = i; ty = j;
            }
            if (a[i][j] == 3) {
                lx = i; ly = j;
            }
        }
    }

    dfs(tx, ty, mou);

    if (minans != INT_MAX) printf("%d\n", minans);
    else printf("-1\n");

    return 0;
}
