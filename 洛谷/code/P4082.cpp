#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1505 * 1505;
const int MAXS = MAXV << 2;

int n, m, q;
int width, total;
int startA, startB;

char grid[MAXV];

int go[4];

int dfn[MAXV];
int low[MAXV];
int cntd;

int sta[MAXV];
int top;

int belong[MAXV];
int vbccCnt;

unsigned char turnMask[MAXS];

unsigned char reach[MAXV];
unsigned char vis[MAXV];

int que[MAXS];

void tarjan(int u) {
    dfn[u] = low[u] = ++cntd;
    sta[++top] = u;

    for (int d = 0; d < 4; d++) {
        int v = u + go[d];

        if (grid[v] == '#') {
            continue;
        }

        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                vbccCnt++;

                int cnt = 0;

                belong[u] = vbccCnt;
                que[++cnt] = u;

                int pop;
                do {
                    pop = sta[top--];
                    belong[pop] = vbccCnt;
                    que[++cnt] = pop;
                } while (pop != v);

                // 当前点双中，每个点连接了哪些方向
                for (int i = 1; i <= cnt; i++) {
                    int x = que[i];
                    int mask = 0;

                    for (int nd = 0; nd < 4; nd++) {
                        int y = x + go[nd];

                        if (belong[y] == vbccCnt) {
                            mask |= 1 << nd;
                        }
                    }

                    // 同一点双中的这些方向可以互相绕到
                    for (int nd = 0; nd < 4; nd++) {
                        if (mask & (1 << nd)) {
                            turnMask[(x << 2) | nd] |= mask;
                        }
                    }
                }
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void addState(int box, int d, int &tail) {
    int bit = 1 << d;

    if (vis[box] & bit) {
        return;
    }

    vis[box] |= bit;
    que[++tail] = (box << 2) | d;
}

void solve() {
    int head = 1;
    int tail = 0;

    // 箱子不动，将箱子位置当作障碍
    reach[startA] = 1;
    que[++tail] = startA;

    while (head <= tail) {
        int u = que[head++];

        for (int d = 0; d < 4; d++) {
            int v = u + go[d];

            if (v == startB) {
                continue;
            }

            if (grid[v] == '#' || reach[v]) {
                continue;
            }

            reach[v] = 1;
            que[++tail] = v;
        }
    }

    head = 1;
    tail = 0;

    // Bessie最开始能够走到箱子的哪些方向
    for (int d = 0; d < 4; d++) {
        int side = startB + go[d];

        if (grid[side] != '#' && reach[side]) {
            addState(startB, d, tail);
        }
    }

    while (head <= tail) {
        int state = que[head++];

        int box = state >> 2;
        int d = state & 3;

        // 箱子不动，Bessie绕到其他方向
        int mask = turnMask[state];

        for (int nd = 0; nd < 4; nd++) {
            if (mask & (1 << nd)) {
                addState(box, nd, tail);
            }
        }

        // Bessie在方向d，箱子向相反方向移动
        int newBox = box + go[d ^ 2];

        if (grid[newBox] != '#') {
            addState(newBox, d, tail);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;

    width = m + 2;
    total = (n + 2) * width;

    go[0] = -width;
    go[1] = 1;
    go[2] = width;
    go[3] = -1;

    memset(grid, '#', sizeof(grid));

    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;

        for (int j = 1; j <= m; j++) {
            int id = i * width + j;

            grid[id] = str[j - 1];

            if (grid[id] == 'A') {
                startA = id;
                grid[id] = '.';
            } else if (grid[id] == 'B') {
                startB = id;
                grid[id] = '.';
            }
        }
    }

    for (int i = 0; i < total; i++) {
        if (grid[i] != '#' && dfn[i] == 0) {
            tarjan(i);
        }
    }

    solve();

    while (q--) {
        int r, c;
        cin >> r >> c;

        int id = r * width + c;

        if (id == startB || vis[id] != 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}