// 长链剖分优化动态规划模版题，C++版
// 一共有n个节点，给定n-1条边，所有节点连成一棵树，规定1号节点是头
// 规定任何点到自己的距离为0
// 定义d(u, x)，以u为头的子树中，到u的距离为x的节点数
// 对于每个点u，想知道哪个尽量小的x，能取得最大的d(u, x)值
// 打印每个点的答案x
// 1 <= n <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/CF1009F
// 测试链接 : https://codeforces.com/problemset/problem/1009/F
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//优化动态规划的方式是节点继承自己长儿子的信息
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;

int n;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 0;

int len[MAXN];
int son[MAXN];
int dfn[MAXN];
int cntd = 0;

// 动态规划
int dp[MAXN];
// 答案数组
int ansx[MAXN];

void setdp(int u, int i, int v) {
    dp[dfn[u] + i] = v;
}

int getdp(int u, int i) {
    return dp[dfn[u] + i];
}

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs1(int u, int fa) {
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa) {
            if (son[u] == 0 || len[son[u]] < len[v]) {
                son[u] = v;
            }
        }
    }
    len[u] = len[son[u]] + 1;
}

//首先去自己的重儿子  因为自己的重儿子占据的位置是自己的范围
//然后去自己的轻儿子  轻儿子占据的和自己所要占据的位置完全不同
//然后开始填自己的位置  每个位置从距离自己0开始  这样重儿子还没有被利用的也不会被覆盖
//轻儿子的没有影响  所以正确
void dfs2(int u, int fa) {
    dfn[u] = ++cntd;
    setdp(u, 0, 1);
    ansx[u] = 0;
    if (son[u] == 0) {
        return;
    }
    dfs2(son[u], u);
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa && v != son[u]) {
            dfs2(v, u);
        }
    }
    // 注意一定要在合并其他儿子dp信息的过程中，去更新ansx
    // 千万不要，最后再遍历一遍u的dp信息，然后更新ansx
    // 因为任何for循环，都不能是长链的规模！
    // 如果for循环是长链的规模，那么u遍历下去，u的重儿子又遍历下去，长链上每个节点都遍历下去
    // 时间复杂度必然不再是O(n)，而是O(n^2)，长链剖分的优势就不存在了！
    // 比如 全图就是一条链  那么时间复杂度相当于O(n^2)
    // 所以长链信息会被u直接继承，绝对不要有任何与长链的长度等规模的循环出现！
    // 这里合并的时间复杂度是O(n)  原因是每条长链只会在来到父亲节点的时候被暴力合并一次
    // 也就是所有的点只会被用一次
    ansx[u] = ansx[son[u]] + 1;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa && v != son[u]) {
            for (int i = 1; i <= len[v]; i++) {
                setdp(u, i, getdp(u, i) + getdp(v, i - 1));
                if (getdp(u, i) > getdp(u, ansx[u]) || (getdp(u, i) == getdp(u, ansx[u]) && i < ansx[u])) {
                    ansx[u] = i;
                    //在过程中更新答案
                }
            }
        }
    }
    // 如果u的某个距离，获得的最大节点数为1
    // 那么u答案就是0距离，因为u到u自己的距离是0，也有1个节点了
    // 根据题目要求，返回尽量小的距离
    if (getdp(u, ansx[u]) == 1) {
        ansx[u] = 0;
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
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ansx[i] << "\n";
    }
    return 0;
}