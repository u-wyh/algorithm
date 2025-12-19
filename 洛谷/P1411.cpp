#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 705;

vector<int> graph[MAXN];
long long dp[MAXN][MAXN]; // dp[u][j]: 以u为根，包含u的连通块大小为j时，其他连通块的最大贡献
int sz[MAXN];
int n;

void dfs(int u, int parent) {
    sz[u] = 1;
    // 初始化：不切任何边时，包含u的连通块大小为1，其他连通块贡献为1（乘积单位元）
    dp[u][1] = 1;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        
        dfs(v, u);
        
        // 临时数组，用于更新dp值
        long long temp[MAXN];
        for (int j = 0; j <= sz[u]; j++) {
            temp[j] = dp[u][j];
        }
        
        // 更新子树大小
        int old_size = sz[u];
        sz[u] += sz[v];
        
        // 初始化新的dp值
        memset(dp[u], 0, sizeof(long long) * (sz[u] + 1));
        
        // 背包DP：考虑是否切断u-v边
        for (int j = old_size; j >= 1; j--) {
            if (temp[j] == 0) continue;
            
            // 情况1：切断u-v边，v子树独立
            // v子树的贡献是dp[v][0]（整个v子树的最大分数）
            long long cut_value = temp[j] * dp[v][0];
            if (cut_value > dp[u][j]) {
                dp[u][j] = cut_value;
            }
            
            // 情况2：不切断u-v边，合并连通块
            for (int k = 1; k <= sz[v]; k++) {
                if (dp[v][k] == 0) continue;
                
                // 合并后包含u的连通块大小为j+k
                long long merge_value = temp[j] * dp[v][k];
                if (j + k <= sz[u] && merge_value > dp[u][j + k]) {
                    dp[u][j + k] = merge_value;
                }
            }
        }
    }
    
    // 计算整个子树的最大分数：考虑包含u的连通块的贡献
    dp[u][0] = 0;
    for (int j = 1; j <= sz[u]; j++) {
        // 总分数 = 其他连通块贡献 * 包含u的连通块大小
        long long total = dp[u][j] * j;
        if (total > dp[u][0]) {
            dp[u][0] = total;
        }
    }
}

int main() {
    cin >> n;
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    // 初始化dp数组
    memset(dp, 0, sizeof(dp));
    
    dfs(1, 0);
    cout << dp[1][0] << endl;
    
    return 0;
}