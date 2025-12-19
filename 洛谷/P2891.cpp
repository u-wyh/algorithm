#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 500;  // 最大节点数
const int INF = 1e9;

struct Edge {
    int to, cap, rev;
};

vector<Edge> graph[MAXN];
int level[MAXN], iter[MAXN];

void addEdge(int from, int to, int cap) {
    graph[from].push_back({to, cap, (int)graph[to].size()});
    graph[to].push_back({from, 0, (int)graph[from].size() - 1});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto &e : graph[v]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < graph[v].size(); i++) {
        Edge &e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
}

int main() {
    int N, F, D;
    cin >> N >> F >> D;
    
    // 节点编号分配：
    // 0: 源点
    // 1-F: 食物节点
    // F+1 - F+N: 奶牛的入点
    // F+N+1 - F+2N: 奶牛的出点
    // F+2N+1 - F+2N+D: 饮料节点
    // F+2N+D+1: 汇点
    
    int source = 0;
    int sink = F + 2 * N + D + 1;
    
    // 源点 → 食物
    for (int i = 1; i <= F; i++) {
        addEdge(source, i, 1);
    }
    
    // 饮料 → 汇点
    for (int i = 1; i <= D; i++) {
        addEdge(F + 2 * N + i, sink, 1);
    }
    
    // 奶牛入点 → 奶牛出点
    for (int i = 1; i <= N; i++) {
        addEdge(F + i, F + N + i, 1);
    }
    
    // 读取每头奶牛的偏好
    for (int i = 1; i <= N; i++) {
        int Fi, Di;
        cin >> Fi >> Di;
        
        // 食物 → 奶牛入点
        for (int j = 0; j < Fi; j++) {
            int food;
            cin >> food;
            addEdge(food, F + i, 1);
        }
        
        // 奶牛出点 → 饮料
        for (int j = 0; j < Di; j++) {
            int drink;
            cin >> drink;
            addEdge(F + N + i, F + 2 * N + drink, 1);
        }
    }
    
    cout << maxFlow(source, sink) << endl;
    
    return 0;
}