// 定向道路，C++版
// 图中有n个点、n条无向边
// 图中可能有多个连通块，保证每个连通块都是一棵基环树
// 你可以给每条边分配一个方向，要求得到的有向图不能出现环
// 计算有多少种定向的方案，答案对 1000000007 取余
// 2 <= n <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF711D
// 测试链接 : https://codeforces.com/problemset/problem/711/D
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200001;
const int MOD = 1000000007;
int n, cntb;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg;

int dfn[MAXN];
int cntd;

int from[MAXN];
// all[x] = 第x棵基环树的节点总数 = 第x棵基环树的边总数
int all[MAXN];
// cycle[x] = 第x棵基环树的环上节点数 = 第x棵基环树的环上边数
int cycle[MAXN];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

ll power(ll x, ll p) {
    ll ans = 1;
    while (p > 0) {
        if ((p & 1) == 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ans;
}

void dfs(int u) {
    dfn[u] = ++cntd;
    all[cntb]++;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (dfn[v] == 0) {
            from[v] = u;
            dfs(v);
        } else if (dfn[u] < dfn[v]) {
            cycle[cntb]++;
            for (int i = v; i != u; i = from[i]) {
                cycle[cntb]++;
            }
        }
    }
}

ll compute() {
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            cntb++;
            dfs(i);
            ll a = power(2, all[cntb]);
            // 这里应该是all[cntb] - cycle[cntb]  但是环上的方向也是可以选择的
            ll b = power(2, all[cntb] - cycle[cntb] + 1);
            ans = ans * ((a - b + MOD) % MOD) % MOD;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        addEdge(i, x);
        addEdge(x, i);
    }
    ll ans = compute();
    cout << ans << "\n";
    return 0;
}