// 用途：判断无向图能否分成边只连接两侧的二分图，并输出每个点所属侧。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 注意：n、m≤200000；无向边双向加入，自环直接判否。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005, MAXM = 200005;
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], edgeCount;
int color[MAXN], que[MAXN];

void addEdge(int u, int v) {
    to[++edgeCount] = v;
    nxt[edgeCount] = head[u];
    head[u] = edgeCount;
}

bool colorComponent(int start) {
    // 每个连通块单独 BFS；相邻点必须染成 1 与 2 两种相反颜色。
    int left = 0, right = 0;
    que[right++] = start;
    color[start] = 1;
    while (left < right) {
        int u = que[left++];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            // 自环或奇环会使一条边两端颜色相同。
            if (color[v] == color[u]) return false;
            if (color[v] == 0) {
                color[v] = 3 - color[u];
                que[right++] = v;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int u = 1; u <= n; ++u) {
        if (color[u] == 0 && !colorComponent(u)) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    for (int u = 1; u <= n; ++u)
        cout << color[u] << (u == n ? '\n' : ' ');
    return 0;
}
