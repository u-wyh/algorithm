// 用途：回答多次询问：树上是否存在距离恰为 k 的两个不同节点。
// 时间：O(nm log n)，n 为点数，m 为询问数。
// 空间：O(n+K)，K 为最大询问距离，用布尔数组记录已处理的距离。
// 注意：边权为正，n≤10000、m≤100、k≤10000000；距离超过最大询问可剪枝。
// 例题：https://www.luogu.com.cn/problem/P3806
// 题意：给定带权树和多个 k，逐个判断有没有一对点的路径长度等于 k。
// 思路：每层选重心；先查当前子树距离能否与先前子树凑成 k，再插入当前子树。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10001;
const int MAXM = 101;
const int MAXV = 10000001;

int n, m;

int query[MAXM];
int maxk;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int weight[MAXN << 1];
int cntg;

bool vis[MAXN];
int siz[MAXN];

// 从u出发，到当前子树的每个节点，收集路径权值和
int cur[MAXN];
int cntc;

// 从u出发，到之前所有子树的每个节点，收集路径权值和
int all[MAXN];
int cnta;

// 使用数组替代哈希表，因为哈希表常数时间大，会超时
bool exist[MAXV];

bool ans[MAXM];

void addEdge(int u, int v, int w) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    weight[cntg] = w;
    head[u] = cntg;
}

void getSize(int u, int fa) {
    siz[u] = 1;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v != fa && !vis[v]) {
            getSize(v, u);
            siz[u] += siz[v];
        }
    }
}

int getCentroid(int u, int fa) {
    getSize(u, fa);
    int half = siz[u] >> 1;
    bool find = false;
    while (!find) {
        find = true;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v != fa && !vis[v] && siz[v] > half) {
                fa = u;
                u = v;
                find = false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u, int fa, int dis) {
    if (dis > maxk) {
        return;
    }
    cur[++cntc] = dis;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v != fa && !vis[v]) {
            dfs(v, u, dis + weight[e]);
        }
    }
}

void calc(int u) {
    cnta = 0;
    exist[0] = true; // 重心本身到重心的距离为 0。
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) {
            cntc = 0;
            dfs(v, u, weight[e]);
            // 先查询、后加入：只会配到前面子树的点，避免在同一子树内配对。
            for (int i = 1; i <= m; i++) {
                for (int j = 1; !ans[i] && j <= cntc; j++) {
                    if (query[i] - cur[j] >= 0) {
                        ans[i] |= exist[query[i] - cur[j]];
                    }
                }
            }
            for (int i = 1; i <= cntc; i++) {
                all[++cnta] = cur[i];
                exist[cur[i]] = true;
            }
        }
    }
    // 只清除这一层写过的距离；下一个重心不能沿用旧记录。
    for (int i = 1; i <= cnta; i++) {
        exist[all[i]] = false;
    }
}

void solve(int u) {
    vis[u] = true;
    calc(u);
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) {
            solve(getCentroid(v, u));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    for (int i = 1; i <= m; i++) {
        cin >> query[i];
        maxk = max(maxk, query[i]);
    }
    solve(getCentroid(1, 0));
    for (int i = 1; i <= m; i++) {
        if (ans[i]) {
            cout << "AYE" << '\n';
        } else {
            cout << "NAY" << '\n';
        }
    }
    return 0;
}
