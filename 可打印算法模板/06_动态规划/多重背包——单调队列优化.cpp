// 用途：每种面值的硬币数量有限，凑出指定金额并使硬币张数最少，同时还原各面值使用数。
// 时间：O(nW)，W 为目标金额。
// 空间：O(nW)，需要为还原方案保存每种面值的选择。
// 注意：n≤200、W≤20000，面值须为正；凑不出时输出 -1。
// 题意：输入 n 种面值、每种的可用张数和目标金额 W，输出最少张数及每种硬币选几张。
// 思路：按金额对当前面值取模分组；单调队列维护该组中可转移的最优旧状态。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205, MAXW = 20005, INF = 1000000000;
int n, W, val[MAXN], num[MAXN];
int f[MAXW], g[MAXW], q[MAXW];
int chosen[MAXN][MAXW], answer[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> val[i];
    for (int i = 1; i <= n; ++i) cin >> num[i];
    cin >> W;

    fill(f + 1, f + W + 1, INF);
    for (int i = 1; i <= n; ++i) {
        copy(f, f + W + 1, g); // 本轮只能从处理前 i-1 种硬币的状态转移。
        for (int r = 0; r < val[i] && r <= W; ++r) {
            int head = 0, tail = 0;
            for (int k = r; k <= W; k += val[i]) {
                // 同余组下标 k 的转移：g[j]+(k-j)/val[i]，且最多用 num[i] 张。
                while (head < tail && (k - q[head]) / val[i] > num[i]) ++head;
                if (g[k] < INF) {
                    // 维护 g[k] - k/val 的递增队列，队首给出当前最少张数。
                    int score = g[k] - (k - r) / val[i];
                    while (head < tail &&
                           g[q[tail - 1]] - (q[tail - 1] - r) / val[i] >= score)
                        --tail;
                    q[tail++] = k;
                }
                f[k] = INF;
                if (head < tail) {
                    int from = q[head];
                    f[k] = g[from] + (k - from) / val[i];
                    chosen[i][k] = (k - from) / val[i];
                }
            }
        }
    }

    if (f[W] == INF) {
        cout << -1 << '\n';
        return 0;
    }
    cout << f[W] << '\n';
    // 从最后一种硬币倒推：chosen[i][sum] 是达到当前金额所用的第 i 种张数。
    for (int i = n, sum = W; i >= 1; --i) {
        answer[i] = chosen[i][sum];
        sum -= answer[i] * val[i];
    }
    for (int i = 1; i <= n; ++i)
        cout << answer[i] << (i == n ? '\n' : ' ');
    return 0;
}
