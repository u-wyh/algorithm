// https://www.spoj.com/problems/DYNALCA/
// 题意：给 n 个点，初始各自为单点有根树。
// 接着给 m 次操作。
// link x y 将根 x 接为另一棵树中 y 的子节点。
// cut x 断开非根节点 x 和它父亲之间的边。
// lca x y 查询同一棵树中两点的最近公共祖先。
// 输出：对每次 lca 逐行输出祖先编号。
// 数据范围：1 <= n, m <= 10^5，
// 点的编号为 1 到 n。
// 难度评分：2300（估算）
// 算法标签：动态树（LCT）

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
int n, m;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];

bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

void rotate(int x) {
    int f = fa[x], g = fa[f];
    if (lr(x) == 0) {
        ls[f] = rs[x];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[x] = f;
    } else {
        rs[f] = ls[x];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[x] = f;
    }
    if (!isroot(f)) {
        if (lr(f) == 0) {
            ls[g] = x;
        } else {
            rs[g] = x;
        }
    }
    fa[f] = x;
    fa[x] = g;
}

void splay(int x) {
    while (!isroot(x)) {
        int f = fa[x];
        if (!isroot(f)) {
            if (lr(x) == lr(f)) {
                rotate(f);
            } else {
                rotate(x);
            }
        }
        rotate(x);
    }
}

int access(int x) {
    int ans = 0;
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        splay(x);
        rs[x] = y;
        ans = x;
    }
    return ans;
}

void makeson(int x, int y) {
    access(x);
    splay(x);
    fa[x] = y;
}

void cutfa(int x) {
    access(x);
    splay(x);
    fa[ls[x]] = 0;
    ls[x] = 0;
}

int lca(int x, int y) {
    if (x == y) {
        return x;
    }
    access(x);
    return access(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
        string op;
        cin >> op;
        if (op == "link") {
            cin >> x >> y;
            makeson(x, y);
        } else if (op == "cut") {
            cin >> x;
            cutfa(x);
        } else {
            cin >> x >> y;
            cout << lca(x, y) << "\n";
        }
    }
    return 0;
}