#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 2500;      // 最大点数：2*35*35 + 2 = 2452
const int MAXM = 30000;     // 最大边数
const int INF = INT_MAX;

// 网络流图结构
struct Edge {
    int to, next;
    long long cap;
    int rev;  // 反向边索引
} edges[MAXM];

int head[MAXN], level[MAXN], cur[MAXN];
int tot = 0;

// 四个方向：上下左右
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int n, m;

// 加边函数
void add_edge(int u, int v, long long cap) {
    edges[tot].to = v;
    edges[tot].cap = cap;
    edges[tot].next = head[u];
    edges[tot].rev = tot + 1;
    head[u] = tot++;
    
    edges[tot].to = u;
    edges[tot].cap = 0;
    edges[tot].next = head[v];
    edges[tot].rev = tot - 1;
    head[v] = tot++;
}

// BFS分层
bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(s);
    level[s] = 0;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (level[v] == -1 && edges[i].cap > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] != -1;
}

// DFS多路增广
long long dfs(int u, int t, long long flow) {
    if (u == t || flow == 0) return flow;
    
    long long total = 0;
    for (int &i = cur[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (level[v] == level[u] + 1 && edges[i].cap > 0) {
            long long f = dfs(v, t, min(flow, edges[i].cap));
            if (f > 0) {
                edges[i].cap -= f;
                edges[edges[i].rev].cap += f;
                total += f;
                flow -= f;
                if (flow == 0) break;
            }
        }
    }
    return total;
}

// Dinic算法主函数
long long dinic(int s, int t) {
    long long total_flow = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        total_flow += dfs(s, t, INF);
    }
    return total_flow;
}

// 获取点的入点编号
inline int get_in(int i, int j) {
    return (i-1)*n + j;
}

// 获取点的出点编号
inline int get_out(int i, int j) {
    return n*n + (i-1)*n + j;
}

int main() {
    cin >> n >> m;
    
    // 初始化图
    memset(head, -1, sizeof(head));
    tot = 0;
    
    // 源点0，汇点T=2*n*n+1
    const int T = 2*n*n + 1;
    
    // 1. 拆点：每个网格点拆为入点和出点
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int u = get_in(i, j);
            int v = get_out(i, j);
            add_edge(u, v, 1);
        }
    }
    
    // 2. 添加起始点（源点到起始点入点）
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        int u = get_in(x, y);
        add_edge(0, u, 1);
    }
    
    // 3. 添加边界点（边界点出点到汇点）
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 1 || i == n || j == 1 || j == n) {
                int u = get_out(i, j);
                add_edge(u, T, 1);
            }
        }
    }
    
    // 4. 添加相邻点之间的边
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                
                // 检查相邻点是否在网格内
                if (ni >= 1 && ni <= n && nj >= 1 && nj <= n) {
                    int u = get_out(i, j);
                    int v = get_in(ni, nj);
                    add_edge(u, v, 1);
                }
            }
        }
    }
    
    // 5. 计算最大流
    long long max_flow = dinic(0, T);
    
    // 6. 判断是否有解
    cout << (max_flow == m ? "YES" : "NO") << endl;
    
    return 0;
}