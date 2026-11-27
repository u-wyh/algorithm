// https://www.luogu.com.cn/problem/P3349
// 题意：输入点数 n、边数 m，
// 给出无向简单图（m 条边）以及一棵 n 个点的树（n-1 条边）。
// 将树的 n 个点一一对应到原图的 n 个点上，
// 要求树中每条边对应的两点在原图中也有边相连。
// 输出合法一一对应的方案总数（无解输出 0）。
// 数据范围：n <= 17，m <= n(n-1)/2。
// 算法标签：树形动态规划、容斥原理、状态压缩
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 18;

int n, m;
bool graph[N][N];  // 原图的邻接矩阵
vector<int> tree[N];  // 树的邻接表
ll dp[N][N];  // dp[u][v]: 以u为根的子树映射到以v为根的方案数

void dfs(int u, int fa, int mask) {
    // 初始化叶子节点
    for (int v = 0; v < n; v++) {
        if (mask >> v & 1) {
            dp[u][v] = 1;
        }
    }
    
    for (int son : tree[u]) {
        if (son == fa) continue;
        dfs(son, u, mask);
        
        // 更新DP值
        for (int v = 0; v < n; v++) {
            if (!(mask >> v & 1)) continue;
            ll sum = 0;
            for (int w = 0; w < n; w++) {
                if ((mask >> w & 1) && graph[v][w]) {
                    sum += dp[son][w];
                }
            }
            dp[u][v] *= sum;
        }
    }
}

int main() {
    cin >> n >> m;
    
    // 读入原图
    memset(graph, false, sizeof(graph));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u][v] = graph[v][u] = true;
    }
    
    // 读入树
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    
    ll ans = 0;
    // 枚举所有子集进行容斥
    for (int mask = 1; mask < (1 << n); mask++) {
        memset(dp, 0, sizeof(dp));
        dfs(0, -1, mask);
        
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                sum += dp[0][i];
            }
        }
        
        // 容斥系数：(-1)^(n - popcount)
        if ((n - __builtin_popcount(mask)) % 2 == 0) {
            ans += sum;
        } else {
            ans -= sum;
        }
    }
    
    cout << ans << endl;
    return 0;
}