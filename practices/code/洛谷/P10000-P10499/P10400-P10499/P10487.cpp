// https://www.luogu.com.cn/problem/P10487
// 题意：每组给一张 n 行 m 列的迷宫。
// M 每秒最多走三格，G 每秒最多走一格。
// 两人上下左右移动，不能穿墙或进入被鬼占领的格子。
// 每秒两只鬼先各扩张两个格距，扩张不受墙阻挡。
// 输出：两人安全相遇的最早时间，无解输出 -1。
// 数据范围：1 <= T <= 3，1 < n, m < 800。
// 每张图恰有一个 M、一个 G 和两个 Z。
// 难度评分：1400（洛谷分级换算）
// 算法标签：广度优先搜索、曼哈顿距离

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 800;
int n, m;
char grid[MAXN][MAXN + 1];
int ghostDistance[MAXN][MAXN];
bool visited[2][MAXN][MAXN];
int cells[2][MAXN * MAXN];
int front[2], back[2];
const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};

bool advance(int person, int steps, int time){
    int unsafeDistance = 2 * time;
    auto& seen = visited[person];
    auto& otherSeen = visited[person ^ 1];
    auto& queue = cells[person];
    for (int step = 0; step < steps; ++step){
        int end = back[person];
        while (front[person] < end){
            int pos = queue[front[person]++];
            int r = pos / m, c = pos % m;
            if (ghostDistance[r][c] <= unsafeDistance){
                continue;
            }
            for (int dir = 0; dir < 4; ++dir){
                int x = r + dr[dir], y = c + dc[dir];
                if (x < 0 || x >= n || y < 0 || y >= m ||
                    grid[x][y] == 'X' || ghostDistance[x][y] <= unsafeDistance ||
                    seen[x][y]){
                    continue;
                }

                // 先到的人可在仍安全的同一格等到这一秒。
                if (otherSeen[x][y]){
                    return true;
                }
                seen[x][y] = true;
                queue[back[person]++] = x * m + y;
            }
        }
    }
    return false;
}

int solve(){
    memset(visited, 0, sizeof(visited));
    front[0] = front[1] = back[0] = back[1] = 0;
    pair<int, int> ghost[2];
    int count = 0;
    for (int r = 0; r < n; ++r){
        cin >> grid[r];
        for (int c = 0; c < m; ++c){
            if (grid[r][c] == 'Z'){
                ghost[count++] = {r, c};
            } else if (grid[r][c] == 'M' || grid[r][c] == 'G'){
                int person = grid[r][c] == 'G';
                visited[person][r][c] = true;
                cells[person][back[person]++] = r * m + c;
            }
        }
    }
    for (int r = 0; r < n; ++r){
        for (int c = 0; c < m; ++c){
            ghostDistance[r][c] = min(abs(r - ghost[0].first) + abs(c - ghost[0].second),
                                      abs(r - ghost[1].first) + abs(c - ghost[1].second));
        }
    }

    for (int time = 1; front[0] < back[0] || front[1] < back[1]; ++time){
        if (advance(0, 3, time) || advance(1, 1, time)){
            return time;
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--){
        cin >> n >> m;
        cout << solve() << '\n';
    }
    return 0;
}
