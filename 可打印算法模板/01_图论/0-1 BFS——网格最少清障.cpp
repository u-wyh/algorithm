// 用途：在含 0/1 代价的网格中，求起点到终点最少清除多少障碍。
// 时间：O(行数×列数)。
// 空间：O(行数×列数)。
// 注意：网格值仅为 0/1；行、列均不超过 1000。
// 例题：https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
// 题意：从左上走到右下，求最少要清除几个障碍。
// 思路：空格边权为 0、障碍边权为 1；双端队列把 0 代价转移放队首。
#include<bits/stdc++.h>
using namespace std;
const int MAXRC = 1005;
int grid[MAXRC][MAXRC], distGrid[MAXRC][MAXRC];

int minimumObstacles(int m, int n) {
    int move[5] = {-1, 0, 1, 0, -1}; // 方向数组：上、右、下、左

    // 初始化距离数组
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) distGrid[i][j] = INT_MAX;
    distGrid[0][0] = 0;

    // 双端队列，存储当前待处理的节点
    deque<pair<int, int>> dq; // 将 deque 改为 dq
    dq.push_front({0, 0});

    while (!dq.empty()) {
        auto record = dq.front();
        dq.pop_front();
        int x = record.first;
        int y = record.second;

        // 如果到达终点，返回当前距离
        if (x == m - 1 && y == n - 1) {
            return distGrid[x][y];
        }

        // 遍历四个方向
        for (int i = 0; i < 4; i++) {
            int nx = x + move[i];
            int ny = y + move[i + 1];

            // 检查新坐标是否在网格范围内
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                // 如果新距离更小，更新距离
                if (distGrid[x][y] + grid[nx][ny] < distGrid[nx][ny]) {
                    distGrid[nx][ny] = distGrid[x][y] + grid[nx][ny];
                    // 如果是空地（0），加入队列前端；否则加入队列后端
                    if (grid[nx][ny] == 0) {
                        dq.push_front({nx, ny});
                    } else {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }
    }

    // 如果无法到达终点，返回 -1
    return -1;
}

int main() {
    // 输入网格大小
    int m, n;
    cin >> m >> n;

    // 输入网格数据
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // 计算并输出结果
    int result = minimumObstacles(m, n);
    cout << result << endl;

    return 0;
}
