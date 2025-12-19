#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_R 130
#define MAX_C 90

int r, c;
int ax[13000], ay[13000];
int next[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int book[MAX_R][MAX_C];
char farm[MAX_R][MAX_C];
int f = 0; // 0 for false, 1 for true

void dfs(int x, int y, int step) {
    if (x < 1 || x > r || y < 1 || y > c) return;
    if (book[x][y]) return;
    if (farm[x][y] == '*') return;
    if (f) return;
    if (x == r && y == c) {
        for (int i = 1; i < step; i++) {
            printf("%d %d\n", ax[i], ay[i]);
        }
        printf("%d %d\n", r, c);
        f = 1;
        return;
    }
    ax[step] = x;
    ay[step] = y;
    book[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        dfs(x + next[i][0], y + next[i][1], step + 1);
        if (f) return;
    }
}

int main() {
    scanf("%d %d", &r, &c);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            scanf(" %c", &farm[i][j]); // 注意在%c前加空格以跳过任何之前的换行符
        }
    }
    dfs(1, 1, 1);
    return 0;
}
