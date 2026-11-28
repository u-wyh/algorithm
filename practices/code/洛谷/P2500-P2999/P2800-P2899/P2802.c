// https://www.luogu.com.cn/problem/P2802
// 题意：输入地图大小 n, m 以及 n 行 m 列的网格，
// 包含障碍物(0)、空地(1)、起点(2)、家(3)、有鼠标的空地(4)。
// 起点满血 6 点，每次向四方向移动一格耗时 1 且扣 1 点血；
// 血量降到 0 立刻死去（在家门口或鼠标格死去也算失败）。
// 走到格 4 且未死时瞬间将血量补满至 6 点（每次经过都能补满），
// 不可静止、不可走障碍或出界。
// 输出一行一个整数，能安全回家输出最短时间，否则输出 -1。
// 数据范围：对于 100% 的数据，1 <= n, m <= 9。
// 难度评分：1000（洛谷分级换算）
// 算法标签：深度优先搜索、回溯、剪枝
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
