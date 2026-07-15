#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 201

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int n, m;
int a[MAX_SIZE][MAX_SIZE];
int s[MAX_SIZE][MAX_SIZE];
int ans = 0;

int dfs(int x, int y) {
    if (s[x][y] != 0) return s[x][y]; // 记忆化搜索
    s[x][y] = 1; // 题目中答案是有包含这个点的
    for (int i = 0; i < 4; i++) {
        int xx = dx[i] + x;
        int yy = dy[i] + y; // 四个方向
        if (xx > 0 && yy > 0 && xx <= n && yy <= m && a[x][y] > a[xx][yy]) {
            dfs(xx, yy);
            s[x][y] = (s[x][y] > s[xx][yy] + 1) ? s[x][y] : s[xx][yy] + 1;
        }
    }
    return s[x][y];
}

int main() {
    scanf("%d%d", &n, &m); // 同题目的R,C
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) { // 找从每个出发的最长距离
        for (int j = 1; j <= m; j++) {
            ans = (ans > dfs(i, j)) ? ans : dfs(i, j); // 取最大值
        }
    }
    printf("%d\n", ans);
    return 0;
}
