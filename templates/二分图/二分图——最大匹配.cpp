#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 505; // 左部节点最大数目
const int MAXM = 505; // 右部节点最大数目

vector<int> adj[MAXN]; // adj[u]存储左部节点u可以连接的右部节点v
int pair_u[MAXN], pair_v[MAXM]; // 匹配数组
int dist[MAXN]; // BFS分层时使用的距离数组
int n, m, e;

bool bfs() {
    queue<int> q;
    memset(dist, -1, sizeof(dist));
    for (int u = 1; u <= n; ++u) {
        if (pair_u[u] == -1) {
            dist[u] = 0;
            q.push(u);
        }
    }
    bool found = false;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (pair_v[v] == -1) {
                found = true;
            } else if (dist[pair_v[v]] == -1) {
                dist[pair_v[v]] = dist[u] + 1;
                q.push(pair_v[v]);
            }
        }
    }
    return found;
}

bool dfs(int u) {
    for (int v : adj[u]) {
        if (pair_v[v] == -1 || (dist[pair_v[v]] == dist[u] + 1 && dfs(pair_v[v]))) {
            pair_u[u] = v;
            pair_v[v] = u;
            return true;
        }
    }
    dist[u] = -1;
    return false;
}

int hopcroft_karp() {
    memset(pair_u, -1, sizeof(pair_u));
    memset(pair_v, -1, sizeof(pair_v));
    int result = 0;
    while (bfs()) {
        for (int u = 1; u <= n; ++u) {
            if (pair_u[u] == -1) {
                if (dfs(u)) {
                    result++;
                }
            }
        }
    }
    return result;
}

int main() {
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 0; i < e; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }
    printf("%d\n", hopcroft_karp());
    return 0;
}