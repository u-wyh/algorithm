#include<bits/stdc++.h>
using namespace std;
#define MAX 105

int n, x1, Y1, ans = 0;
int nums[MAX][MAX], vis[MAX][MAX];

void dfs(int x, int y, int k) {
    if (x < 1 || x > n || y < 1 || y > n || nums[x][y] == 1 || vis[x][y] == 1) {
        // 超出边界、遇到障碍物或已访问过的位置，直接返回
        return;
    }

    vis[x][y] = 1; // 标记当前位置为已访问
    ans = max(ans, k); // 更新最大距离

    // 尝试四个方向的跳跃
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (auto& dir : directions) {
        int nx = x + dir.first, ny = y + dir.second;
        // 注意：这里不需要判断 nx 和 ny 是否已经访问过，因为一旦进入这个函数，nx 和 ny 就是新的、未被访问的位置
        // 如果 nx 和 ny 不满足条件（如超出边界、遇到障碍物），则下面的 dfs 调用不会进行
        dfs(nx, ny, k + 1);
    }

    vis[x][y] = 0; // 回溯，标记当前位置为未访问（如果需要再次访问的话，这步可以省略）
}

int main() {
    memset(vis, 0, sizeof(vis)); // 初始化为0，表示所有位置都未访问
    cin >> n >> x1 >> Y1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> nums[i][j];
        }
    }

    dfs(x1, Y1, 0); // 从起点开始深度优先搜索
    printf("%d\n", ans);
    return 0;
}
