#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // 为了使用bool类型

#define MAX_N 200
#define MAX_LINE_LENGTH 10000 // 假设每行长度不超过10000

int cx[4] = {-1, 1, 0, 0};
int cy[4] = {0, 0, -1, 1}; // 方向数组，上、下、左、右

int a[MAX_N][MAX_N]; // 原始数据，虽然用a，但用f[i][j]逻辑更清晰
int m[MAX_N]; // 存储每行的长度
int n; // 地图的行数
int h = 0; // 岛屿的数量

void dfs(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m[x] || a[x][y] == 0) return; // 边界条件或已访问过
    a[x][y] = 0; // 标记为已访问
    for (int i = 0; i < 4; i++) {
        dfs(x + cx[i], y + cy[i]); // 递归搜索上下左右
    }
}

int main() {
    char buffer[MAX_LINE_LENGTH + 1]; // 读取行的缓冲区
    scanf("%d", &n); // 读入n
    getchar(); // 消耗行尾的换行符

    for (int i = 1; i <= n; i++) {
        fgets(buffer, sizeof(buffer), stdin); // 读取一行
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') buffer[--len] = '\0'; // 去除字符串末尾的换行符
        m[i] = len; // 存储每行的长度

        for (int j = 0; j < len; j++) {
            if (buffer[j] >= 'a' && buffer[j] <= 'z') {
                a[i][j + 1] = 1; // 注意，C语言数组从0开始，但这里为了方便理解，我们使用1开始的索引
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m[i]; j++) {
            if (a[i][j] == 1) {
                dfs(i, j); // 如果当前位置是陆地，开始搜索
                h++; // 每找到一个岛屿，岛屿数量加1
            }
        }
    }

    printf("%d\n", h); // 输出岛屿数量
    return 0;
}
