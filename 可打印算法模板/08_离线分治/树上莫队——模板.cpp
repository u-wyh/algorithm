// 用途：离线求树上两点路径中不同数值的个数。
// 时间：约 O((n+q)√n)。
// 空间：O(n+q+V)。
// 例题：https://www.luogu.com.cn/problem/SP10707
// 题意：多次查询树上两点路径中的不同数值数目。
// 思路：欧拉序把路径转成区间，莫队移动时切换点出现状态并处理 LCA。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 40001;
const int MAXM = 100001;
const int MAXP = 20;

// 查询的参数，jobl、jobr、lca、id
// 如果是类型1，那么lca == 0，表示空缺
// 如果是类型2，那么lca > 0，查询结果需要补充这个单点信息
struct Query {
   int l, r, lca, id;
};

int n, m;
int color[MAXN];
int sorted[MAXN];
int cntv;

Query query[MAXM];

int head[MAXN];
int to[MAXN << 1];
int nxt[MAXN << 1];
int cntg;

// dep是深度
// seg是括号序
// st是节点开始序
// ed是节点结束序
// stjump是倍增表
// cntd是括号序列的长度
int dep[MAXN];
int seg[MAXN << 1];
int st[MAXN];
int ed[MAXN];
int stjump[MAXN][MAXP];
int cntd;

// 分块
int bi[MAXN << 1];

// 窗口信息
bool vis[MAXN];
int cnt[MAXN];
int kind;

int ans[MAXM];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

int kth(int num) {
    int left = 1, right = cntv, mid, ret = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (sorted[mid] <= num) {
            ret = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ret;
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    seg[++cntd] = u;
    st[u] = cntd;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXP; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa) {
            dfs(v, u);
        }
    }
    seg[++cntd] = u;
    ed[u] = cntd;
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    for (int p = MAXP - 1; p >= 0; p--) {
        if (dep[stjump[a][p]] >= dep[b]) {
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = MAXP - 1; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

bool QueryCmp(Query &a, Query &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    return a.r < b.r;
}

// 窗口不管是加入还是删除node
// 只要遇到node就翻转信息即可
void invert(int node) {
    int val = color[node];
    if (vis[node]) {
        if (--cnt[val] == 0) {
            kind--;
        }
    } else {
        if (++cnt[val] == 1) {
            kind++;
        }
    }
    vis[node] = !vis[node];
}

void compute() {
    int winl = 1, winr = 0;
    for (int i = 1; i <= m; i++) {
        int jobl = query[i].l;
        int jobr = query[i].r;
        int lca = query[i].lca;
        int id = query[i].id;
        while (winl > jobl) {
            invert(seg[--winl]);
        }
        while (winr < jobr) {
            invert(seg[++winr]);
        }
        while (winl < jobl) {
            invert(seg[winl++]);
        }
        while (winr > jobr) {
            invert(seg[winr--]);
        }
        // 注意这里  如果需要额外添加一个lca  结束的时候不要忘记删除它  防止污染后面的数据
        if (lca > 0) {
            invert(lca);
        }
        ans[id] = kind;
        if (lca > 0) {
            invert(lca);
        }
    }
}

void prepare() {
    for (int i = 1; i <= n; i++) {
        sorted[i] = color[i];
    }
    sort(sorted + 1, sorted + n + 1);
    cntv = 1;
    for (int i = 2; i <= n; i++) {
        if (sorted[cntv] != sorted[i]) {
            sorted[++cntv] = sorted[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        color[i] = kth(color[i]);
    }
    // 括号序列分块
    int blen = (int) sqrt(cntd);
    for (int i = 1; i <= cntd; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    sort(query + 1, query + m + 1, QueryCmp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    for (int i = 1, u, v, uvlca; i <= m; i++) {
        cin >> u >> v;
        if (st[v] < st[u]) {
            swap(u, v);
        }
        uvlca = lca(u, v);
        if (u == uvlca) {
            query[i].l = st[u];
            query[i].r = st[v];
            query[i].lca = 0;
        } else {
            query[i].l = ed[u];
            query[i].r = st[v];
            query[i].lca = uvlca;
        }
        query[i].id = i;
    }
    prepare();
    compute();
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
