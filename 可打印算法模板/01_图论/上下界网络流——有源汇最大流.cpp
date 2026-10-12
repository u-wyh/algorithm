// 用途：每条有向边有流量下界和上界时，求源点到汇点的最大可行流。
// 时间：两次 Dinic，最坏 O(n²m)。
// 空间：O(n+m)。
// 注意：源汇不同，0≤下界≤上界，流量总和不超过 2×10^18；无解输出 -1。
// 例题：https://loj.ac/p/116
// 题意：每条边有流量上下界，求 s 到 t 的最大可行流。
// 思路：先按下界平衡各点流量并求可行流，再在残量网络中增广 s→t。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205, MAXM = 10005;
const int MAXE = 2 * (MAXM + MAXN + 5);
const long long INF = LLONG_MAX / 4;
int head[MAXN], to[MAXE], nxt[MAXE], edgeCount;
int level[MAXN], current[MAXN], que[MAXN];
int superEdges[MAXN * 2], superCount;
long long capacity[MAXE], balance[MAXN];

int addEdge(int u, int v, long long cap) {
    int forward = edgeCount;
    to[edgeCount] = v;
    capacity[edgeCount] = cap;
    nxt[edgeCount] = head[u];
    head[u] = edgeCount++;
    to[edgeCount] = u;
    capacity[edgeCount] = 0;
    nxt[edgeCount] = head[v];
    head[v] = edgeCount++;
    return forward;
}

bool bfs(int source, int sink, int vertices) {
    fill(level, level + vertices + 1, -1);
    int left = 0, right = 0;
    que[right++] = source;
    level[source] = 0;
    while (left < right) {
        int u = que[left++];
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (capacity[e] > 0 && level[v] == -1) {
                level[v] = level[u] + 1;
                que[right++] = v;
            }
        }
    }
    return level[sink] != -1;
}

long long dfs(int u, int sink, long long pushed) {
    if (u == sink || pushed == 0) return pushed;
    for (int &e = current[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (capacity[e] == 0 || level[v] != level[u] + 1) continue;
        long long flow = dfs(v, sink, min(pushed, capacity[e]));
        if (flow == 0) continue;
        capacity[e] -= flow;
        capacity[e ^ 1] += flow;
        return flow;
    }
    return 0;
}

long long maxflow(int source, int sink, int vertices) {
    long long total = 0;
    while (bfs(source, sink, vertices)) {
        copy(head, head + vertices + 1, current);
        while (long long flow = dfs(source, sink, INF)) total += flow;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(head, head + MAXN, -1);
    int n, m, source, sink;
    cin >> n >> m >> source >> sink;
    int superSource = n + 1, superSink = n + 2;
    for (int i = 0, u, v; i < m; ++i) {
        long long lower, upper;
        cin >> u >> v >> lower >> upper;
        addEdge(u, v, upper - lower);
        balance[u] -= lower;
        balance[v] += lower;
    }
    int returnEdge = addEdge(sink, source, INF);
    long long required = 0;
    for (int u = 1; u <= n; ++u) {
        if (balance[u] > 0) {
            superEdges[superCount++] = addEdge(superSource, u, balance[u]);
            required += balance[u];
        } else if (balance[u] < 0) {
            superEdges[superCount++] = addEdge(u, superSink, -balance[u]);
        }
    }
    if (maxflow(superSource, superSink, superSink) != required) {
        cout << -1 << '\n';
        return 0;
    }
    long long baseFlow = capacity[returnEdge ^ 1];
    // 可行流确定后，移除辅助边，再在原网络的残量图上增广。
    capacity[returnEdge] = capacity[returnEdge ^ 1] = 0;
    for (int i = 0; i < superCount; ++i)
        capacity[superEdges[i]] = capacity[superEdges[i] ^ 1] = 0;
    cout << baseFlow + maxflow(source, sink, superSink) << '\n';
    return 0;
}
