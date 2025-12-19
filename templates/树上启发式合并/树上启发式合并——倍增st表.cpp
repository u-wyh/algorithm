// 表亲数量，C++版
// 一共有n个节点，编号1~n，给定每个节点的父亲节点编号，父亲节点为0，说明当前节点是某棵树的头
// 注意，n个节点组成的是森林结构，可能有若干棵树
// 一共有m条查询，每条查询 x k，含义如下
// 如果x往上走k的距离，没有祖先节点，打印0
// 如果x往上走k的距离，能找到祖先节点a，那么从a往下走k的距离，除了x之外，可能还有其他节点
// 这些节点叫做x的k级表亲，打印这个表亲的数量
// 1 <= n、m <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF208E
// 测试链接 : https://codeforces.com/problemset/problem/208/E
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题我们将他转换成查询一个节点的k级儿子的数量  我们可以查询某一层的节点个数统计
// 但是为了避免不是自己子树中的值扰乱答案  所以我们使用树上启发式合并
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXH = 20;

int n, m;
bool root[MAXN];

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
    cin >> n;
    for (int i = 1, father; i <= n; i++) {
        cin >> father;
        if (father == 0) {
        	root[i] = true;
        } else {
            addEdge(father, i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            dfs1(i, 0);
        }
    }
    cin >> m;
    for (int i = 1, u, k, kfather; i <= m; i++) {
        cin >> u >> k;
        kfather = kAncestor(u, k);
        if (kfather != 0) {
            // 将问题直接挂在祖先节点之上
            addQuestion(kfather, i, k);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            //这个地方必须要写0  虽然他是根  因为我们不想让他影响其他的树
            dfs2(i, 0);
        }
    }
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