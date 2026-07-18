// 世界树，C++版
// 一共有n个节点，给定n-1条无向边，所有节点组成一棵树
// 一共有q条查询，每条查询格式如下
// 查询 k a1 a2 ... ak : 给出了k个不同的管理点，树上每个点都找最近的管理点来管理自己
//                       如果某个节点的最近管理点有多个，选择编号最小的管理点
//                       打印每个管理点，管理的节点数量
// 1 <= n、q <= 3 * 10^5
// 1 <= 所有查询给出的点的总数 <= 3 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3233
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题必须要添加1号点  因为所有关键点可能是一个节点的子树中的节点
// 这个子树之外的节点没有被统计到 
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300001;
const int MAXP = 20;

int n, q, k;

int headg[MAXN];
int nextg[MAXN << 1];
int tog[MAXN << 1];
int cntg;

int headv[MAXN];
int nextv[MAXN];
int tov[MAXN];
int cntv;

int dep[MAXN];
// 注意siz[u]表示在原树里，子树u有几个节点
int siz[MAXN];
int dfn[MAXN];
int stjump[MAXN][MAXP];
int cntd;

int order[MAXN];
int arr[MAXN];
bool isKey[MAXN];
int tmp[MAXN << 1];

// manager[u]表示u节点找到的最近管理点
int manager[MAXN];
// dist[u]表示u节点到最近管理点的距离
int dist[MAXN];
// ans[i]表示i这个管理点，管理了几个点
int ans[MAXN];

bool cmp(int x, int y) {
    return dfn[x] < dfn[y];
}

void addEdgeG(int u, int v) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

void addEdgeV(int u, int v) {
    nextv[++cntv] = headv[u];
    tov[cntv] = v;
    headv[u] = cntv;
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    dfn[u] = ++cntd;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXP; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = headg[u]; e; e = nextg[e]) {
        int v = tog[e];
        if (v != fa) {
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
}

int getLca(int a, int b) {
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

int buildVirtualTree() {
    sort(arr + 1, arr + k + 1, cmp);
    int len = 0;
    // 这里加入1号点
    tmp[++len] = 1;
    for (int i = 1; i < k; i++) {
        tmp[++len] = arr[i];
        tmp[++len] = getLca(arr[i], arr[i + 1]);
    }
    tmp[++len] = arr[k];
    sort(tmp + 1, tmp + len + 1, cmp);
    int unique = 1;
    for (int i = 2; i <= len; i++) {
        if (tmp[unique] != tmp[i]) {
            tmp[++unique] = tmp[i];
        }
    }
    cntv = 0;
    for (int i = 1; i <= unique; i++) {
        headv[tmp[i]] = 0;
    }
    for (int i = 1; i < unique; i++) {
        addEdgeV(getLca(tmp[i], tmp[i + 1]), tmp[i + 1]);
    }
    return tmp[1];
}

// 下方找最近管理点，节点u根据孩子的管理点，找到离u最近的管理点
void dp1(int u) {
    dist[u] = 1000000001;
    for (int e = headv[u]; e; e = nextv[e]) {
        int v = tov[e];
        dp1(v);
        int w = dep[v] - dep[u];
        if (dist[v] + w < dist[u] || (dist[v] + w == dist[u] && manager[v] < manager[u])) {
            dist[u] = dist[v] + w;
            manager[u] = manager[v];
        }
    }
    if (isKey[u]) {
        dist[u] = 0;
        manager[u] = u;
    }
}

// 上方找最近管理点，根据u找到的最近管理点，更新每个孩子节点v的最近管理点
// 这就是为什么一定要添加1号点的原因
void dp2(int u) {
    for (int e = headv[u]; e; e = nextv[e]) {
        int v = tov[e];
        int w = dep[v] - dep[u];
        if (dist[u] + w < dist[v] || (dist[u] + w == dist[v] && manager[u] < manager[v])) {
            dist[v] = dist[u] + w;
            manager[v] = manager[u];
        }
        dp2(v);
    }
}

// 已知u一定是v的祖先节点，u到v之间的大量节点没有被纳入到虚树
// 这部分节点之前都分配给了manager[u]，现在根据最近距离做重新分配
// 可能若干节点会重新分配给manager[v]，修正相关的计数
void amend(int u, int v) {
    if (manager[u] == manager[v]) {
        return;
    }
    int x = v;
    // 二分找到分界线
    for (int p = MAXP - 1; p >= 0; p--) {
        int jump = stjump[x][p];
        if (dep[u] < dep[jump]) {
            int tou = dep[jump] - dep[u] + dist[u];
            int tov = dep[v] - dep[jump] + dist[v];
            if (tov < tou || (tov == tou && manager[v] < manager[u])) {
                x = jump;
            }
        }
    }
    int delta = siz[x] - siz[v];
    ans[manager[u]] -= delta;
    ans[manager[v]] += delta;
}

// 每个点都有了最近的管理点，更新相关管理点的管理节点计数
void dp3(int u) {
    // u的管理节点，先获得原树里子树u的所有节点
	// 然后经历修正的过程，把管理节点的数量更新正确
    ans[manager[u]] += siz[u];
    for (int e = headv[u]; e; e = nextv[e]) {
        int v = tov[e];
        // 修正的过程
        amend(u, v);
        // 马上要执行dp3(v)，所以子树v的节点现在扣除
        ans[manager[u]] -= siz[v];
        // 子树v怎么分配节点，那是后续dp3(v)的事情
        dp3(v);
    }
}

void compute() {
    for (int i = 1; i <= k; i++) {
        arr[i] = order[i];
    }
    for (int i = 1; i <= k; i++) {
        isKey[arr[i]] = true;
        ans[arr[i]] = 0;
    }
    int tree = buildVirtualTree();
    dp1(tree);
    dp2(tree);
    dp3(tree);
    for (int i = 1; i <= k; i++) {
        isKey[arr[i]] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdgeG(u, v);
        addEdgeG(v, u);
    }
    dfs(1, 0);
    cin >> q;
    for (int t = 1; t <= q; t++) {
        cin >> k;
        for (int i = 1; i <= k; i++) {
            cin >> order[i];
        }
        compute();
        for (int i = 1; i <= k; i++) {
            cout << ans[order[i]] << ' ';
        }
        cout << '\n';
    }
    return 0;
}