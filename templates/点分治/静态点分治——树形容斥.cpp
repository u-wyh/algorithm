// 消息传递，C++版
// 一共有n个节点，给定n-1条边，每条边的权值为1，所有节点组成一棵树
// 一共有m条查询，格式 x k : 打印有多少点与x的距离恰好为k
// 1 <= n、m <= 10^5
// 0 <= k < n
// 测试链接 : https://www.luogu.com.cn/problem/P6626
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题的大思路是将所有子树中的查询全部收集起来  计算路径经过当前头结点的方案数
// 容斥的目的是要减去子树中本身不该被访问的错误答案
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int t, n, m;

int headg[MAXN];
int nextg[MAXN << 1];
int tog[MAXN << 1];
int cntg;

int headq[MAXN];
int nextq[MAXN];
int dis[MAXN];
int qid[MAXN];
int cntq;

bool vis[MAXN];
int siz[MAXN];

// nodeCnt[i] = j，表示从u往下走i条边，一共能找到j个点
int nodeCnt[MAXN];
int maxEdge;

struct Node {
   int need, qid;
};

Node arr[MAXN];
int cnta;

int ans[MAXN];

void addEdge(int u, int v) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

void addQuery(int u, int k, int id) {
    nextq[++cntq] = headq[u];
    dis[cntq] = k;
    qid[cntq] = id;
    headq[u] = cntq;
}

void getSize(int u, int fa) {
    siz[u] = 1;
    for (int e = headg[u]; e; e = nextg[e]) {
        int v = tog[e];
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
        for (int e = headg[u]; e; e = nextg[e]) {
            int v = tog[e];
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

void dfs(int u, int fa, int edge) {
    nodeCnt[edge]++;
    maxEdge = max(maxEdge, edge);
    for (int e = headq[u]; e; e = nextq[e]) {
        if (dis[e] >= edge) {
            arr[++cnta] = { dis[e] - edge, qid[e] };
        }
    }
    for (int e = headg[u]; e; e = nextg[e]) {
        int v = tog[e];
        if (v != fa && !vis[v]) {
            dfs(v, u, edge + 1);
        }
    }
}

// 如果这个effect是负数
// 那么只会减去这个节点的子树中涉及到的提问  而这些提问才是真正会影响答案的错误答案
void calc(int u, int edge, int effect) {
    cnta = 0;
    maxEdge = 0;
    dfs(u, 0, edge);
    for (int i = 1; i <= cnta; i++) {
        ans[arr[i].qid] += nodeCnt[arr[i].need] * effect;
    }
    for (int v = 0; v <= maxEdge; v++) {
        nodeCnt[v] = 0;
    }
}

void solve(int u) {
    vis[u] = true;
    calc(u, 0, 1);
    for (int e = headg[u]; e; e = nextg[e]) {
        int v = tog[e];
        if (!vis[v]) {
            // 其实容斥很关键的地方是 calc去的是v
            // solve去的是v所在子树的重心
            calc(v, 1, -1);
            solve(getCentroid(v, u));
        }
    }
}

void prepare() {
    cntg = 0;
    cntq = 0;
    for (int i = 1; i <= n; i++) {
        headg[i] = 0;
        headq[i] = 0;
        vis[i] = false;
    }
    for (int i = 1; i <= m; i++) {
        ans[i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int c = 1; c <= t; c++) {
        cin >> n >> m;
        prepare();
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
        }
        for (int i = 1, x, k; i <= m; i++) {
            cin >> x >> k;
            addQuery(x, k, i);
        }
        solve(getCentroid(1, 0));
        for (int i = 1; i <= m; i++) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}