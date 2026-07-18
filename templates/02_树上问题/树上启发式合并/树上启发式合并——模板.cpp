// 树上启发式合并模版题，C++版
// 一共有n个节点，编号1~n，给定n-1条边，所有节点连成一棵树，1号节点为树头
// 每个节点给定一种颜色值，一共有m条查询，每条查询给定参数x
// 每条查询打印x为头的子树上，一共有多少种不同的颜色
// 1 <= n、m、颜色值 <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/U41492
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;
// 每个节点的颜色
int arr[MAXN];

// 链式前向星
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cnt = 0;

// 树链剖分
int fa[MAXN];
int siz[MAXN];
int son[MAXN];

// 树上启发式合并
// colorCnt[i] = j，表示i这种颜色出现了j次
int colorCnt[MAXN];
int ans[MAXN];
int diffColors = 0;

void addEdge(int u, int v) {
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

// 重链剖分
void dfs1(int u, int f) {
    fa[u] = f;
    siz[u] = 1;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            siz[u] += siz[v];
            if (son[u] == 0 || siz[son[u]] < siz[v]) {
                son[u] = v;
            }
        }
    }
}

// 子树u每个节点贡献信息
void effect(int u) {
    if (++colorCnt[arr[u]] == 1) {
        diffColors++;
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u]) {
            effect(v);
        }
    }
}

// 子树u每个节点取消贡献
void cancle(int u) {
    colorCnt[arr[u]] = 0; // 出现任何颜色，直接把该颜色的计数重置为0
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u]) {
            cancle(v);
        }
    }
}

// 树上启发式合并的过程
void dfs2(int u, int keep) {
    // 遍历轻儿子的子树，统计子树的答案，然后取消贡献
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            dfs2(v, 0);
        }
    }
    // 遍历重儿子的子树，统计子树的答案，然后保留贡献
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    // 当前节点贡献信息
    if (++colorCnt[arr[u]] == 1) {
        diffColors++;
    }
    // 遍历轻儿子的子树，重新贡献一遍
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            effect(v);
        }
    }
    // 记录子树u的答案
    ans[u] = diffColors;
    // 如果u是上级节点的轻儿子，子树u的贡献取消，否则保留
    if (keep == 0) {
        diffColors = 0;
        cancle(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    dfs1(1, 0);//重链剖分 得出重儿子信息即可
    dfs2(1, 0);//从头结点开始向下统计信息 这里也可以写成 dfs2(1,1)
    cin >> m;
    for (int i = 1, cur; i <= m; i++) {
        cin >> cur;
        cout << ans[cur] << "\n";
    }
    return 0;
}