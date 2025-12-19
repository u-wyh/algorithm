// https://www.luogu.com.cn/problem/P2045
// 这道题是求出最大费用最大流，我们将所有的值取反  就变成了最小费用最大流问题
// 涉及到了负数  不建议使用dijkstra  所以我们使用spfa实现
// 但是在一般情况下  即使出现了负数  也很难形成负环
// 时间复杂度O(F × V × E)  f为最大流值
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int MAXV = 5005; // 最大顶点数 = 2*n*n + 2
const int MAXE = 50005; // 最大边数
const int INF = 0x3f3f3f3f;

int n, K,s,t;
int grid[MAXN][MAXN];

// 链式前向星存储图
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int cap[MAXE];
int cost[MAXE];
int cnt=2;

// 最小费用最大流相关数组
int dist[MAXV], pre[MAXV], preEdge[MAXV];
bool inQueue[MAXV];

void addEdge(int u, int v, int w, int c) {
    to[cnt] = v;
    cap[cnt] = w;
    cost[cnt] = c;
    nxt[cnt] = head[u];
    head[u] = cnt++;
    
    to[cnt] = u;
    cap[cnt] = 0;
    cost[cnt] = -c;
    nxt[cnt] = head[v];
    head[v] = cnt++;
}

// 最小费用最大流
int minCostMaxFlow() {
    int totalFlow = 0, totalCost = 0;
    
    while (true) {
        // 初始化距离和前驱数组
        memset(dist, 0x3f, sizeof(dist));
        memset(inQueue, false, sizeof(inQueue));
        memset(pre, 0, sizeof(pre));
        memset(preEdge, 0, sizeof(preEdge));
        
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        inQueue[s] = true;
        
        // SPFA找最短路
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;
            
            for (int i = head[u]; i ; i = nxt[i]) {
                int v = to[i];
                if (cap[i] > 0 && dist[v] > dist[u] + cost[i]) {
                    dist[v] = dist[u] + cost[i];
                    pre[v] = u;
                    preEdge[v] = i;
                    
                    if (!inQueue[v]) {
                        inQueue[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        
        // 如果无法到达汇点，退出
        if (dist[t] == INF) break;
        
        // 计算增广路径上的最小容量
        int flow = INF;
        for (int u = t; u != s; u = pre[u]) {
            int edgeIdx = preEdge[u];
            flow = min(flow, cap[edgeIdx]);
        }
        
        // 更新流量和费用
        totalFlow += flow;
        totalCost += flow * dist[t];
        
        // 更新残余网络
        for (int u = t; u != s; u = pre[u]) {
            int edgeIdx = preEdge[u];
            cap[edgeIdx] -= flow;
            cap[edgeIdx ^ 1] += flow; // 反向边
        }
    }
    
    return -totalCost; // 返回最大费用
}

int main() {
    cin >> n >> K;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
        }
    }
    
    if (K == 0) {
        cout << 0 << endl;
        return 0;
    }
    
    s = 2 * n * n + 1;
    t=s+1;
    
    addEdge(s, 1, K, 0);
    
    addEdge(2 * n * n, t, K, 0);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int inNode = (i - 1) * n + j;
            int outNode = n * n + (i - 1) * n + j;
            
            // 入点到出点：取数的边（容量1，费用为负的格子值）
            addEdge(inNode, outNode, 1, -grid[i][j]);
            
            // 入点到出点：经过但不取数的边（容量K-1，费用0）
            if (K > 1) {
                addEdge(inNode, outNode, K - 1, 0);
            }
            
            // 出点到右边格子的入点
            if (j < n) {
                int rightIn = (i - 1) * n + j + 1;
                addEdge(outNode, rightIn, K, 0);
            }
            
            // 出点到下边格子的入点
            if (i < n) {
                int downIn = i * n + j;
                addEdge(outNode, downIn, K, 0);
            }
        }
    }
    
    int result = minCostMaxFlow();
    cout << result << endl;
    
    return 0;
}