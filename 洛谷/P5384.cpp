#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;
const int MAXH = 22;

int n, m;

// 链式前向星建图
int headg[MAXN];
int nextg[MAXN];
int tog[MAXN];
int cntg;

// 问题列表
int headq[MAXN];
int nextq[MAXN];
int ansiq[MAXN];
int kq[MAXN];
int cntq;

// 树链剖分
int siz[MAXN];
int dep[MAXN];
int son[MAXN];
int stjump[MAXN][MAXH];//表示这个节点的2的j次方祖先

// 树上启发式合并
int depCnt[MAXN];
int ans[MAXN];

void addEdge(int u, int v) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

void addQuestion(int u, int i, int k) {
    nextq[++cntq] = headq[u];
    ansiq[cntq] = i;//表示问题编号
    kq[cntq] = k;
    headq[u] = cntq;
}

void dfs1(int u, int fa) {
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[ stjump[u][p - 1] ][p - 1];
    }
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        dfs1(tog[e], u);
    }
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        siz[u] += siz[v];
        if (son[u] == 0 || siz[son[u]] < siz[v]) {
            son[u] = v;
        }
    }
}

//查询u的k级祖先
int kAncestor(int u, int k) {
    for (int p = MAXH - 1; p >= 0; p--) {
        if (k >= (1 << p)) {
            k -= (1 << p);
            u = stjump[u][p];
        }
    }
    return u;
}

void effect(int u) {
    depCnt[dep[u]]++;
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        effect(tog[e]);
    }
}

void cancle(int u) {
    depCnt[dep[u]]--;
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        cancle(tog[e]);
    }
}

void dfs2(int u, int keep) {
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        if (v != son[u]) {
            dfs2(v, 0);
        }
    }
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    depCnt[dep[u]]++;
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        if (v != son[u]) {
            effect(v);
        }
    }
    for (int i = headq[u]; i > 0; i = nextq[i]) {
    	ans[ansiq[i]] = depCnt[dep[u] + kq[i]];
    }
    if (keep == 0) {
        cancle(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n>>m;
    for (int i = 2, father; i <= n; i++) {
        cin >> father;
        addEdge(father, i);
    }
    dfs1(1,0);
    for (int i = 1, u, k, kfather; i <= m; i++) {
        cin >> u >> k;
        kfather = kAncestor(u, k);
        if (kfather != 0) {
            // 将问题直接挂在祖先节点之上
            addQuestion(kfather, i, k);
        }
    }
    dfs2(1,1);
    for (int i = 1; i <= m; i++) {
        if (ans[i] == 0) {
            cout << "0 ";
        } else {
            cout << ans[i] - 1 << " ";
        }
    }
    cout << "\n";
    return 0;
}