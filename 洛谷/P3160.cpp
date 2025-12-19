#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MOD = 12345678;
const int MAXN = 5;
const int MAXM = 8;
const int MAXS = 1 << 8;

int n, m,ans;
char grid[MAXN][MAXM];
int x[10], y[10], cnt; // 局部极小值位置
int f[MAXS][MAXN * MAXM + 1]; // DP数组
bool blocked[MAXN][MAXM]; // 标记哪些位置不能放置

// 检查坐标是否在范围内
bool inRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

// 计算当前状态下的方案数
int solve() {
    cnt = 0;
    // 收集所有局部极小值位置
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'X') {
                x[cnt] = i;
                y[cnt] = j;
                cnt++;
            }
        }
    }
    
    // 初始化DP数组
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    
    // 状态压缩DP
    for (int state = 0; state < (1 << cnt); state++) {
        // 标记哪些位置被阻塞（不能放置）
        memset(blocked, 0, sizeof(blocked));
        for (int i = 0; i < cnt; i++) {
            if (!(state & (1 << i))) {
                // 对于未放置的局部极小值，阻塞其周围8个位置
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int nx = x[i] + dx, ny = y[i] + dy;
                        if (inRange(nx, ny)) {
                            blocked[nx][ny] = true;
                        }
                    }
                }
            }
        }
        
        // 计算可放置位置数量
        int available = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!blocked[i][j]) available++;
            }
        }
        
        // DP转移
        for (int k = 0; k < n * m; k++) {
            if (f[state][k] == 0) continue;
            
            // 放置到非局部极小值位置
            if (available - k > 0) {
                f[state][k + 1] = (f[state][k + 1] + 1LL * f[state][k] * (available - k) % MOD) % MOD;
            }
            
            // 放置到局部极小值位置
            for (int i = 0; i < cnt; i++) {
                if (!(state & (1 << i))) {
                    int newState = state | (1 << i);
                    f[newState][k + 1] = (f[newState][k + 1] + f[state][k]) % MOD;
                }
            }
        }
    }
    
    return f[(1 << cnt) - 1][n * m];
}

// 容斥搜索
void dfs(int i, int j, int sign) {
    if (j == m) {
        dfs(i + 1, 0, sign);
        return;
    }
    if (i == n) {
        // 到达终点，计算当前状态
        ans = (ans + sign * solve() + MOD) % MOD;
        return;
    }
    
    // 不将当前位置设为局部极小值
    dfs(i, j + 1, sign);
    
    // 尝试将当前位置设为局部极小值（如果合法）
    if (grid[i][j] == '.') {
        // 检查周围是否已经有局部极小值
        bool valid = true;
        for (int dx = -1; dx <= 1 && valid; dx++) {
            for (int dy = -1; dy <= 1 && valid; dy++) {
                int ni = i + dx, nj = j + dy;
                if (inRange(ni, nj) && grid[ni][nj] == 'X') {
                    valid = false;
                }
            }
        }
        
        if (valid) {
            grid[i][j] = 'X';
            dfs(i, j + 1, -sign); // 容斥符号取反
            grid[i][j] = '.';
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    
    // 检查初始局部极小值是否相邻
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'X') {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        int ni = i + dx, nj = j + dy;
                        if (inRange(ni, nj) && grid[ni][nj] == 'X') {
                            cout << 0 << endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    
    // 开始容斥搜索
    ans = 0;
    dfs(0, 0, 1);
    
    cout << ans << endl;
    return 0;
}