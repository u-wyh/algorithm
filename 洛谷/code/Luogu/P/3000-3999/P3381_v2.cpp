#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
typedef long long LL;
const LL INF = (1LL << 60);

struct Edge {
    int from, to;
    LL cap, cost;
    Edge(int from, int to, LL cap, LL cost) 
        : from(from), to(to), cap(cap), cost(cost) {}
};

struct MinCostMaxFlow {
    int n;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<LL> dist, incf;
    vector<int> pre;
    vector<bool> inq;

    MinCostMaxFlow(int n) : n(n), graph(n), dist(n), incf(n), pre(n), inq(n) {}

    void addEdge(int from, int to, LL cap, LL cost) {
        graph[from].push_back(edges.size());
        edges.push_back(Edge(from, to, cap, cost));
        graph[to].push_back(edges.size());
        edges.push_back(Edge(to, from, 0, -cost));
    }

    pair<LL, LL> minCostMaxFlow(int s, int t) {
        LL max_flow = 0, min_cost = 0;
        while (true) {
            dist.assign(n, INF);
            incf.assign(n, 0);
            inq.assign(n, false);
            
            queue<int> q;
            q.push(s);
            dist[s] = 0;
            incf[s] = INF;
            inq[s] = true;
            
            while (!q.empty()) {
                int u = q.front(); q.pop();
                inq[u] = false;
                for (int idx : graph[u]) {
                    Edge &e = edges[idx];
                    if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                        dist[e.to] = dist[u] + e.cost;
                        pre[e.to] = idx;
                        incf[e.to] = min(incf[u], e.cap);
                        if (!inq[e.to]) {
                            q.push(e.to);
                            inq[e.to] = true;
                        }
                    }
                }
            }
            
            if (dist[t] == INF) break;
            
            LL flow = incf[t];
            max_flow += flow;
            min_cost += flow * dist[t];
            
            for (int v = t; v != s; v = edges[pre[v]].from) {
                edges[pre[v]].cap -= flow;
                edges[pre[v]^1].cap += flow;
            }
        }
        return {max_flow, min_cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;  // 转换为0-based索引
    
    MinCostMaxFlow mcmf(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        LL cap, cost;
        cin >> u >> v >> cap >> cost;
        u--; v--;  // 转换为0-based索引
        mcmf.addEdge(u, v, cap, cost);
    }
    
    auto [max_flow, min_cost] = mcmf.minCostMaxFlow(s, t);
    cout << max_flow << " " << min_cost << endl;
    
    return 0;
}