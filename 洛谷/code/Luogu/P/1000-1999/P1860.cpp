#include <bits/stdc++.h>
using namespace std;

const int MAXN = 65;
const int MAXM = 245;
const int MAXV = 1005;
const int MAXK = 35;
const int INF = 1e9;
const int NEG = -1e9;

int N, M, V, K;

// buy[i] 表示第 i 种药水的购买价格
// sell[i] 表示第 i 种药水的回收价格
int buyPrice[MAXN], sellPrice[MAXN];

// 魔法信息
// product[i] 表示第 i 个魔法的成品
// cnt[i] 表示第 i 个魔法需要多少个原料
// mat[i][j] 表示第 i 个魔法的第 j 个原料
int product[MAXM];
int cnt[MAXM];
int mat[MAXM][MAXN];

// cost[i][k]：用 k 次魔法做出一个 i 号药水的最小成本
int cost[MAXN][MAXK];

// dp[k][v]：用了 k 次魔法，花了 v 元时，最多能获得多少回收收入
int dp[MAXK][MAXV];

// 临时数组，用于处理一个魔法内部的原料组合
int g[MAXN][MAXK];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> V >> K;

    for (int i = 1; i <= N; i++) {
        cin >> buyPrice[i] >> sellPrice[i];
    }

    for (int i = 1; i <= M; i++) {
        cin >> product[i] >> cnt[i];
        for (int j = 1; j <= cnt[i]; j++) {
            cin >> mat[i][j];
        }
    }

    // 初始化 cost
    for (int i = 1; i <= N; i++) {
        for (int k = 0; k <= K; k++) {
            cost[i][k] = INF;
        }
    }

    // 不使用魔法时，只能直接购买
    for (int i = 1; i <= N; i++) {
        cost[i][0] = buyPrice[i];
    }

    /*
        计算 cost[i][k]

        如果某个魔法是：
            a + b + c -> x

        那么做出 x 需要额外消耗 1 次魔法。
        如果总共用了 t 次魔法，那么原料内部最多分配 t - 1 次魔法。
    */
    for (int t = 1; t <= K; t++) {
        for (int m = 1; m <= M; m++) {
            int x = product[m];
            int c = cnt[m];

            // 初始化临时 DP
            for (int i = 0; i <= c; i++) {
                for (int j = 0; j <= t - 1; j++) {
                    g[i][j] = INF;
                }
            }

            g[0][0] = 0;

            // 依次处理每个原料
            for (int i = 1; i <= c; i++) {
                int id = mat[m][i];

                for (int used = 0; used <= t - 1; used++) {
                    for (int give = 0; give <= used; give++) {
                        if (g[i - 1][used - give] == INF) continue;
                        if (cost[id][give] == INF) continue;

                        g[i][used] = min(
                            g[i][used],
                            g[i - 1][used - give] + cost[id][give]
                        );
                    }
                }
            }

            // 原料一共用了 t - 1 次魔法，再用 1 次魔法合成成品
            cost[x][t] = min(cost[x][t], g[c][t - 1]);
        }
    }

    // 初始化背包 DP
    for (int k = 0; k <= K; k++) {
        for (int v = 0; v <= V; v++) {
            dp[k][v] = NEG;
        }
    }

    dp[0][0] = 0;

    /*
        完全背包：

        每种药水可以做多个。
        每个方案是：
            花费 cost[i][useMagic]
            消耗 useMagic 次魔法
            获得 sellPrice[i] 的回收收入
    */
    for (int i = 1; i <= N; i++) {
        for (int useMagic = 0; useMagic <= K; useMagic++) {
            int c = cost[i][useMagic];

            if (c == INF) continue;
            if (c > V) continue;

            for (int k = useMagic; k <= K; k++) {
                for (int v = c; v <= V; v++) {
                    if (dp[k - useMagic][v - c] == NEG) continue;

                    dp[k][v] = max(
                        dp[k][v],
                        dp[k - useMagic][v - c] + sellPrice[i]
                    );
                }
            }
        }
    }

    int ans = 0;

    // 最终利润 = 回收收入 - 初始投入成本
    for (int k = 0; k <= K; k++) {
        for (int v = 0; v <= V; v++) {
            if (dp[k][v] == NEG) continue;
            ans = max(ans, dp[k][v] - v);
        }
    }

    cout << ans << '\n';

    return 0;
}