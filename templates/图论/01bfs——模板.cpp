// 到达角落需要移除障碍物的最小数目
// 给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n
// 每个单元格都是两个值之一：
// 0 表示一个 空 单元格，
// 1 表示一个可以移除的 障碍物
// 你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。
// 现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1)
// 返回需要移除的障碍物的最小数目
// 测试链接 : https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
#include<bits/stdc++.h>
using namespace std;

int minimumObstacles(vector<vector<int>>& grid) {
    int move[5] = {-1, 0, 1, 0, -1}; // 方向数组：上、右、下、左
    int m = grid.size();
    int n = grid[0].size();

    // 初始化距离数组
    vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
    distance[0][0] = 0;

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
            return distance[x][y];
        }

        // 遍历四个方向
        for (int i = 0; i < 4; i++) {
            int nx = x + move[i];
            int ny = y + move[i + 1];

            // 检查新坐标是否在网格范围内
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                // 如果新距离更小，更新距离
                if (distance[x][y] + grid[nx][ny] < distance[nx][ny]) {
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];
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
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // 计算并输出结果
    int result = minimumObstacles(grid);
    cout << result << endl;

    return 0;
}