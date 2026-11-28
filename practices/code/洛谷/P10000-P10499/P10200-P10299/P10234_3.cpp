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
const int to[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const char direction[] = "DRUL";

int n, m;
char grid[MAXN][MAXN];
bool vis[MAXN][MAXN];
unsigned char ways[MAXN][MAXN];

struct Node{
    int x, y;
};

void bfs(){
    queue<Node> q;
    q.push({1, 1});
    vis[1][1] = true;
    while(!q.empty()){
        Node u = q.front();
        q.pop();
        if(u.x == n && u.y == m){
            stack<char> path;
            for(int x = n, y = m; x != 1 || y != 1; ){
                int d = ways[x][y];
                path.push(direction[d]);
                int back = (d + 2) % 4;
                x += to[back][0];
                y += to[back][1];
            }
            printf("%zu\n", path.size());
            while(!path.empty()){
                putchar(path.top());
                path.pop();
            }
            putchar('\n');
            return;
        }
        for(int d = 0; d < 4; ++d){
            int x = u.x + to[d][0], y = u.y + to[d][1];
            if(x >= 1 && x <= n && y >= 1 && y <= m &&
               !vis[x][y] && grid[x][y] != grid[u.x][u.y]){
                vis[x][y] = true;
                ways[x][y] = d;
                q.push({x, y});
            }
        }
    }
    puts("-1");
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i){
            scanf("%2000s", grid[i] + 1);
            fill(vis[i] + 1, vis[i] + m + 1, false);
        }
        bfs();
    }
    return 0;
}
