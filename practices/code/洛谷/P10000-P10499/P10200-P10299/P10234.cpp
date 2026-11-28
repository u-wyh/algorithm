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
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const char directions[] = "DURL";

int n, m;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN];
unsigned char from[MAXN][MAXN];

struct Cell{
    int x, y;
};

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        cin >> (grid[i] + 1);
        fill(dist[i] + 1, dist[i] + m + 1, -1);
    }

    queue<Cell> q;
    q.push({1, 1});
    dist[1][1] = 0;
    while(!q.empty()){
        Cell u = q.front();
        q.pop();
        if(u.x == n && u.y == m){
            break;
        }
        for(int d = 0; d < 4; ++d){
            int x = u.x + dx[d], y = u.y + dy[d];
            if(x < 1 || x > n || y < 1 || y > m ||
               dist[x][y] != -1 || grid[x][y] == grid[u.x][u.y]){
                continue;
            }
            dist[x][y] = dist[u.x][u.y] + 1;
            from[x][y] = d;
            q.push({x, y});
        }
    }

    int length = dist[n][m];
    cout << length << '\n';
    if(length == -1){
        return;
    }
    string path(length, ' ');
    int x = n, y = m;
    for(int i = length - 1; i >= 0; --i){
        int d = from[x][y];
        path[i] = directions[d];
        x -= dx[d];
        y -= dy[d];
    }
    cout << path << '\n';
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
