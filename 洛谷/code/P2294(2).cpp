#include <bits/stdc++.h>
using namespace std;

template <typename Int>
inline Int read()
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
    return init * flag;
}

struct Edge {
    int to, v;
};
#define make_edge(u, v) ((Edge){(u), (v)})
vector<Edge> G[5007];
int n, m;
int dis[5007];
bool inq[5007];
int vis[5007];

int once()
{
    // [read data]
    n = read<int>();
    m = read<int>();
    for (int i = 0; i <= n + 1; i++) G[i].clear();
    for (int i = 1, u, v, w; i <= m; i++) {
        u = read<int>();
        v = read<int>();
        w = read<int>();
        G[u - 1].push_back(make_edge(v, w)); // sum_{u-1} + w <= sum_{v}
        G[v].push_back(make_edge(u - 1, -w)); // sum_{v} - w <= sum_{u-1}
    }
    for (int i = 0; i <= n; i++)
        G[n + 1].push_back(make_edge(i, 0));
    // [/read data]
    // [spfa]
    queue<int> q;
    q.push(n + 1);
    memset(dis, 0xcf, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(inq, 0, sizeof(inq));
    dis[n + 1] = 0;
    while (!q.empty()) {
        int fr = q.front();
        q.pop();
        inq[fr] = 0;
        for (unsigned i = 0; i < G[fr].size(); i++) {
            if (dis[G[fr][i].to] < dis[fr] + G[fr][i].v) {
                dis[G[fr][i].to] = dis[fr] + G[fr][i].v;
                if (!inq[G[fr][i].to]) {
                    vis[G[fr][i].to]++;
                    if (vis[G[fr][i].to] > n) {
                        puts("false");
                        return 0;
                    }
                    inq[G[fr][i].to] = true;
                    q.push(G[fr][i].to);
                }
            }
        }
    }
    // [/spfa]
    puts("true");
    return 0;
}

int main()
{
    int T = read<int>();
    while (T--) once();
    return 0;
}
