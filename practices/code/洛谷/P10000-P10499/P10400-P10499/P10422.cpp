// https://www.luogu.com.cn/problem/P10422
// 题意：给 N 点 M 边的无向图和初始血量 HP。
// 每个点各有一只怪物，每条边有移动耗时。
// 从 0 号点出发，到一个点可选择击杀当地怪物。
// 击杀不耗时，但每只仍活着的邻点怪物会攻击一次。
// 输出：杀完所有怪物并以正血量到达 N-1 的
// 最短耗时，无解输出 -1。
// 数据范围：1 <= N <= 15，1 <= M <= N^2。
// 1 <= HP <= 100，攻击力与边权均在 [1, 10]。
// 难度评分：2000（洛谷分级换算）
// 算法标签：状态压缩动态规划、Floyd

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAX_HP = 100;
const int INF = 1000000;
const int NO_TIME = numeric_limits<uint16_t>::max();

int n, m, hp;
int alarmPower[MAXN], neighbors[MAXN];
int attackSum[1 << MAXN];
int travel[MAXN][MAXN];

// killed 必含 last，数组下标省去这一位。
uint16_t best[1 << (MAXN - 1)][MAXN][MAX_HP];
uint8_t minDamage[1 << (MAXN - 1)][MAXN];

int withoutBit(int mask, int pos){
    int low = mask & ((1 << pos) - 1);
    return low | ((mask >> (pos + 1)) << pos);
}

int solve(){
    int all = (1 << n) - 1;
    memset(best, 0xff, (1 << (n - 1)) * sizeof(best[0]));
    for (int mask = 1; mask <= all; ++mask){
        for (int bits = mask; bits; bits &= bits - 1){
            int last = __builtin_ctz(bits);
            int packed = withoutBit(mask, last);
            int damage = attackSum[(all ^ mask) & neighbors[last]];
            int least = hp;
            if (damage < hp){
                int previous = mask ^ (1 << last);
                if (!previous){
                    best[packed][last][damage] = travel[0][last];
                    least = damage;
                } else {
                    for (int pre = previous; pre; pre &= pre - 1){
                        int from = __builtin_ctz(pre);
                        int oldPacked = withoutBit(previous, from);
                        int oldLeast = minDamage[oldPacked][from];
                        if (oldLeast + damage >= hp){
                            continue;
                        }
                        least = min(least, oldLeast + damage);
                        int cost = travel[from][last];
                        const auto& oldBest = best[oldPacked][from];
                        auto& newBest = best[packed][last];
                        for (int d = oldLeast; d + damage < hp; ++d){
                            int nextTime = oldBest[d] + cost;
                            if (nextTime < newBest[d + damage]){
                                newBest[d + damage] = nextTime;
                            }
                        }
                    }
                }
            }
            minDamage[packed][last] = least;
        }
    }

    int ans = INF;
    for (int last = 0; last < n; ++last){
        int packed = withoutBit(all, last);
        for (int d = minDamage[packed][last]; d < hp; ++d){
            int cost = best[packed][last][d];
            if (cost != NO_TIME){
                ans = min(ans, cost + travel[last][n - 1]);
            }
        }
    }
    return ans == INF ? -1 : ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> hp;
    for (int i = 0; i < n; ++i){
        cin >> alarmPower[i];
        fill(travel[i], travel[i] + n, INF);
        travel[i][i] = 0;
    }
    for (int i = 0; i < m; ++i){
        int u, v, weight;
        cin >> u >> v >> weight;
        travel[u][v] = travel[v][u] = min(travel[u][v], weight);
        if (u != v){
            neighbors[u] |= 1 << v;
            neighbors[v] |= 1 << u;
        }
    }

    // 只有击杀才掉血，击杀之间可以走任意最短路。
    for (int k = 0; k < n; ++k){
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                travel[i][j] = min(travel[i][j], travel[i][k] + travel[k][j]);
            }
        }
    }
    for (int i = 0; i < n; ++i){
        if (travel[0][i] == INF){
            cout << -1 << '\n';
            return 0;
        }
    }
    for (int mask = 1; mask < (1 << n); ++mask){
        attackSum[mask] = attackSum[mask & (mask - 1)] + alarmPower[__builtin_ctz(mask)];
    }

    cout << solve() << '\n';
    return 0;
}