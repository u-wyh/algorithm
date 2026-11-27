// https://www.luogu.com.cn/problem/P6008
// 题意：给定 N x M
// 的壁画网格（边界全为石头 '#'，内部有空位 '.' 或石头 '#'），
// 第 i 行高度为 N + 1 - i；
// 现向部分空格填水，
// 要求若格子 a 有水且
// 存在只经过高度不超过 a 的空格/水格的四连通路径到达 b，则 b 也必须有水
// 求合法方案数（模 10^9 + 7）。
// 数据范围：1 <= N, M <= 1000。
// 算法标签：并查集、动态规划
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_SIZE = 1005;
const int MAX_NM = (MAX_SIZE + 2) * (MAX_SIZE + 2);
const ll MOD = 1e9 + 7;

// 全局数组定义
int n, m;
ll ans = 1;
int fa[MAX_NM];
ll dp[MAX_NM];
bool grid[MAX_SIZE][MAX_SIZE];
bool visited[MAX_NM];

inline int index(int i, int j) {
    return (i - 1) * m + j;
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void un(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        fa[fx] = fy;
        dp[fy] = (dp[fy] * dp[fx]) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    const int dirs[3][2] = {{1, 0}, {0, 1}, {0, -1}};

    // 初始化并查集
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int idx = index(i, j);
            fa[idx] = idx;
            dp[idx] = 1;
        }
    }

    // 读取网格
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j) {
            grid[i][j] = (s[j-1] == '#');
        }
    }

    // 处理网格
    for (int i = n-1; i >= 2; --i) {
        
        for (int j = 2; j <= m-1; ++j) {
            if (grid[i][j]) continue;
            for (const auto& d : dirs) {
                int ni = i + d[0], nj = j + d[1];
                if (ni >= 1 && ni <= n && nj >= 1 && nj <= m && !grid[ni][nj]) {
                    un(index(i, j), index(ni, nj));
                }
            }
        }

        memset(visited, 0, sizeof(visited)); // 重置访问标记
        for (int j = 2; j <= m-1; ++j) {
            if (grid[i][j]) continue;
            int root = find(index(i, j));
            if (!visited[root]) {
                visited[root] = true;
                dp[root] = (dp[root] + 1) % MOD;
            }
        }
    }

    // 计算结果
    for (int i = 2; i <= n-1; ++i) {
        for (int j = 2; j <= m-1; ++j) {
            if (grid[i][j]) continue;
            int idx = index(i, j);
            if (find(idx) == idx) {
                ans = (ans * dp[idx]) % MOD;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}