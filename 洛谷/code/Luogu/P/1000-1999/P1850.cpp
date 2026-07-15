#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005; // 修改为2005，因为n最大2000
const int MAXV = 305;
const int INF = 1e9;

int n, m, v, e;
int dis[MAXV][MAXV];
int a[MAXN], b[MAXN]; // 增大数组大小
double c[MAXN];
double dp[MAXN][MAXN][2]; // 增大数组大小

void floyd() {
    for (int k = 1; k <= v; k++) {
        for (int i = 1; i <= v; i++) {
            for (int j = 1; j <= v; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &v, &e);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &c[i]);
    }
    
    // 初始化距离矩阵
    for (int i = 1; i <= v; i++) {
        for (int j = 1; j <= v; j++) {
            dis[i][j] = (i == j) ? 0 : INF;
        }
    }
    
    // 读入边
    for (int i = 1; i <= e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (u != v) {
            dis[u][v] = min(dis[u][v], w);
            dis[v][u] = dis[u][v];
        }
    }
    
    // Floyd 计算所有教室间的最短距离
    floyd();
    
    // 初始化DP数组
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }
    
    // 正确初始化第一个时间段
    dp[1][0][0] = 0;
    dp[1][1][1] = 0; // 修复：申请的状态应该是1
    
    // DP转移
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= min(i, m); j++) {
            // 当前不申请
            double t1 = dp[i-1][j][0] + dis[a[i-1]][a[i]];
            double t2 = dp[i-1][j][1] 
                        + (1 - c[i-1]) * dis[a[i-1]][a[i]] 
                        + c[i-1] * dis[b[i-1]][a[i]];
            dp[i][j][0] = min(t1, t2);
            
            // 当前申请（需要j>=1）
            if (j >= 1) {
                // 前一个不申请，当前申请
                double t3 = dp[i-1][j-1][0] 
                            + (1 - c[i]) * dis[a[i-1]][a[i]] 
                            + c[i] * dis[a[i-1]][b[i]];
                
                // 前一个申请，当前申请
                double t4 = dp[i-1][j-1][1] 
                            + (1 - c[i-1]) * (1 - c[i]) * dis[a[i-1]][a[i]]
                            + (1 - c[i-1]) * c[i] * dis[a[i-1]][b[i]]
                            + c[i-1] * (1 - c[i]) * dis[b[i-1]][a[i]]
                            + c[i-1] * c[i] * dis[b[i-1]][b[i]];
                
                dp[i][j][1] = min(t3, t4);
            }
        }
    }
    
    // 寻找最优解
    double ans = INF;
    for (int j = 0; j <= m; j++) {
        ans = min(ans, min(dp[n][j][0], dp[n][j][1]));
    }
    printf("%.2lf", ans);
    return 0;
}