// 桥梁，C++版
// 有n个点组成的无向图，依次给出m条无向边
// u v w : u到v的边，边权为w，边权同时代表限重
// 如果开车从边上经过，车的重量 <= 边的限重，车才能走过这条边
// 接下来有q条操作，每条操作的格式如下
// 操作 1 eid tow : 编号为eid的边，边权变成tow
// 操作 2 nid car : 编号为nid的点出发，车重为car，查询能到达几个不同的点
// 1 <= n <= 5 * 10^4    0 <= m <= 10^5
// 1 <= q <= 10^5        1 <= 其他数据 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P5443
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const int MAXM = 100001;
const int MAXQ = 100001;

int n, m, q;
int blen, bnum;

int u[MAXM];
int v[MAXM];
int w[MAXM];

int op[MAXQ];
int eid[MAXQ];
int tow[MAXQ];
int nid[MAXQ];
int car[MAXQ];

// edge是所有边的编号
// change表示边的分类
// curw表示边最新的权值
int edge[MAXM];
bool change[MAXM];
int curw[MAXM];

// operate是所有操作的编号
// query是当前操作块查询操作的编号
// update是当前操作块修改操作的编号
int operate[MAXQ];
int query[MAXQ];
int update[MAXQ];

// 可撤销并查集
int fa[MAXN];
int siz[MAXN];
int rollback[MAXM][2];
int opsize = 0;

// 归并的辅助数组
int arr1[MAXM];
int arr2[MAXM];

// 所有查询的答案
int ans[MAXQ];

void build() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        siz[i] = 1;
    }
}

int find(int x) {
    while (x != fa[x]) {
        x = fa[x];
    }
    return x;
}

void Union(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) {
        return;
    }
    if (siz[fx] < siz[fy]) {
        swap(fx, fy);
    }
    fa[fy] = fx;
    siz[fx] += siz[fy];
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
    for (int fx, fy; opsize > 0; opsize--) {
        fx = rollback[opsize][0];
        fy = rollback[opsize][1];
        fa[fy] = fy;
        siz[fx] -= siz[fy];
    }
}

void merge() {
    int siz1 = 0, siz2 = 0;
    for (int i = 1; i <= m; i++) {
        if (change[edge[i]]) {
            arr1[++siz1] = edge[i];
        } else {
            arr2[++siz2] = edge[i];
        }
    }
    sort(arr1 + 1, arr1 + siz1 + 1, [&](int x, int y) { return w[x] > w[y]; });
    int i = 0, p1 = 1, p2 = 1;
    while (p1 <= siz1 && p2 <= siz2) {
        edge[++i] = w[arr1[p1]] >= w[arr2[p2]] ? arr1[p1++] : arr2[p2++];
    }
    while (p1 <= siz1) {
        edge[++i] = arr1[p1++];
    }
    while (p2 <= siz2) {
        edge[++i] = arr2[p2++];
    }
}

// 当前操作编号[l..r]，之前的所有修改操作都已生效
// 所有边的编号edge[1..m]，按照边权从大到小排序
// 处理当前操作块的所有操作
void compute(int l, int r) {
    // 重建并查集，目前没有任何连通性
	// 清空边的修改标记
    build();
    memset(change + 1, 0, m * sizeof(bool));
    int cntu = 0, cntq = 0;
    for (int i = l; i <= r; i++) {
        if (op[operate[i]] == 1) {
            change[eid[operate[i]]] = true;
            update[++cntu] = operate[i];
        } else {
            query[++cntq] = operate[i];
        }
    }
    // 查询操作的所有编号，根据车重从大到小排序
	// 然后依次处理所有查询
    sort(query + 1, query + cntq + 1, [&](int x, int y) { return car[x] > car[y]; });
    for (int i = 1, j = 1; i <= cntq; i++) {
        // 边权 >= 当前车重 的边全部连上，注意这是不回退的
        while (j <= m && w[edge[j]] >= car[query[i]]) {
            if (!change[edge[j]]) {
                Union(u[edge[j]], v[edge[j]]);
            }
            j++;
        }
        // 注意需要用可撤销并查集，撤销会改值的边
        opsize = 0;
        // 会改值的边，边权先继承改之前的值
        for (int k = 1; k <= cntu; k++) {
            curw[eid[update[k]]] = w[eid[update[k]]];
        }
        // 修改操作的时序 < 当前查询操作的时序，那么相关边的边权改成最新值
        for (int k = 1; k <= cntu && update[k] < query[i]; k++) {
            curw[eid[update[k]]] = tow[update[k]];
        }
        // 会改值的边，其中 边权 >= 当前车重 的边全部连上
        for (int k = 1; k <= cntu; k++) {
            if (curw[eid[update[k]]] >= car[query[i]]) {
                Union(u[eid[update[k]]], v[eid[update[k]]]);
            }
        }
        // 并查集修改完毕，查询答案
        ans[query[i]] = siz[find(nid[query[i]])];
        // 并查集的撤销
        undo();
    }
    // 所有会改值的边，边权修改，因为即将去下个操作块
    for (int i = 1; i <= cntu; i++) {
        w[eid[update[i]]] = tow[update[i]];
    }
    // 没改值的边和改了值的边，根据边权从大到小合并
    merge();
}

void prepare() {
    blen = max(1, (int)sqrt(q * log2(n)));
    bnum = (q + blen - 1) / blen;
    sort(edge + 1, edge + m + 1, [&](int x, int y) { return w[x] > w[y]; });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        edge[i] = i;
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> op[i];
        if (op[i] == 1) {
            cin >> eid[i] >> tow[i];
        } else {
            cin >> nid[i] >> car[i];
        }
        operate[i] = i;
    }
    prepare();
    for (int i = 1, l, r; i <= bnum; i++) {
        l = (i - 1) * blen + 1;
        r = min(i * blen, q);
        compute(l, r);
    }
    for (int i = 1; i <= q; i++) {
        if (op[i] == 2) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}