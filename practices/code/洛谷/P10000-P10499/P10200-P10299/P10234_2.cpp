// https://www.luogu.com.cn/problem/P10234
// 题意：每组给 n 行 m 列的 01 矩阵。
// 从左上走到右下，每步只走向数字不同的相邻格。
// 输出：不可达输出 -1，可达输出最短步数和方向串。
// 方向用 L、R、U、D 表示，最短路径任选。
// 数据范围：T 为正整数，1 <= n, m <= 2000。
// 多组数据的 n 之和、m 之和各不超过 2000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：广度优先搜索、路径回溯

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const int walk[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const char directions[] = "DURL";

int n, m;
char grid[MAXN][MAXN];
signed char from[MAXN][MAXN];

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        cin >> (grid[i] + 1);
        fill(from[i] + 1, from[i] + m + 1, -1);
    }

    queue<pair<int, int>> q;
    q.push({1, 1});
    from[1][1] = 4;
    while(!q.empty() && from[n][m] == -1){
        auto [x, y] = q.front();
        q.pop();
        for(int d = 0; d < 4; ++d){
            int nx = x + walk[d][0], ny = y + walk[d][1];
            if(nx < 1 || nx > n || ny < 1 || ny > m ||
               from[nx][ny] != -1 || grid[nx][ny] == grid[x][y]){
                continue;
            }
            from[nx][ny] = d;
            q.push({nx, ny});
        }
    }

    if(from[n][m] == -1){
        cout << "-1\n";
        return;
    }
    string path;
    for(int x = n, y = m; x != 1 || y != 1; ){
        int d = from[x][y];
        path.push_back(directions[d]);
        x -= walk[d][0];
        y -= walk[d][1];
    }
    reverse(path.begin(), path.end());
    cout << path.size() << '\n' << path << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
