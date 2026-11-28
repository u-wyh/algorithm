// https://www.luogu.com.cn/problem/P4438
// 题意：n-1 个城市与 n 个乡村构成以 1 号城市为根的内向二叉树，
// 每个城市需从通向它的 1 条公路和 1 条铁路中恰好翻修 1 条
// 乡村 i 到首都经过 x 条未翻修公路和 y 条未翻修铁路的不便利值为
// c_i*(a_i+x)*(b_i+y)，求所有乡村总不便利值最小值。
// 数据范围：n <= 20000，1 <= a_i, b_i <= 60，
// 1 <= c_i <= 10^9，任意乡村最多经过 40 条道路到达首都。
// 难度评分：1500（洛谷分级换算）
// 算法标签：树形动态规划、深度优先搜索
#include <bits/stdc++.h>
using namespace std;

const int N = 4e4 + 1;
typedef int arr[N];
typedef long long ll;

int n, m, Top, Tot;
arr a, b, c, s, t, Num, S;
ll f[82][41][41];

void dfs(int u, int x, int y) {
    int p = Num[u] = Top ? S[Top--] : ++Tot;
    if (!s[u]) {
        for (int i = 0; i <= x; ++i) {
            for (int j = 0; j <= y; ++j) {
                f[p][i][j] = (ll)c[u] * (a[u] + i) * (b[u] + j);
            }
        }
        return;
    }
    dfs(s[u], x + 1, y);
    dfs(t[u], x, y + 1);
    int ls = Num[s[u]], rs = Num[t[u]];
    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            f[p][i][j] = min(f[ls][i + 1][j] + f[rs][i][j], f[ls][i][j] + f[rs][i][j + 1]);
        }
    }
    S[++Top] = ls;
    S[++Top] = rs;
}

int main() {
    cin >> n;
    m = 2 * n - 1;
    int u, v;
    for (int i = 1; i <= n - 1; ++i) {
        cin >> u >> v;
        s[i] = u < 0 ? n - 1 - u : u;
        t[i] = v < 0 ? n - 1 - v : v;
    }
    for (int i = n; i <= m; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }
    dfs(1, 0, 0);
    cout << f[Num[1]][0][0] << endl;
    return 0;
}
