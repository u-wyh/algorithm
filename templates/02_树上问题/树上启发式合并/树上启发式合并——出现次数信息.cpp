// 颜色平衡的子树，C++版
// 一共有n个节点，编号1~n，给定每个节点的颜色值和父亲节点编号
// 输入保证所有节点一定组成一棵树，并且1号节点是树头
// 如果一棵子树中，存在的每种颜色的节点个数都相同，这棵子树叫颜色平衡树
// 打印整棵树中有多少个子树是颜色平衡树
// 1 <= n、颜色值 <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P9233
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题是通过记录每种颜色出现的次数  以及 出现次数相同的颜色的种类  互相印证  得到答案
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;

int n;
int color[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt = 0;

int siz[MAXN];
int son[MAXN];

// colorCnt[i] = j，表示i这种颜色出现了j次
int colorCnt[MAXN];
// colorNum[i] = j，表示出现次数为i的颜色一共有j种
int colorNum[MAXN];
// 颜色平衡子树的个数
int ans = 0;

void addEdge(int u, int v) {
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

void dfs1(int u) {
    siz[u] = 1;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs1(to[e]);
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        siz[u] += siz[v];
        if (son[u] == 0 || siz[son[u]] < siz[v]) {
            son[u] = v;
        }
    }
}

void effect(int u) {
    colorCnt[color[u]]++;
    colorNum[colorCnt[color[u]] - 1]--;
    colorNum[colorCnt[color[u]]]++;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        effect(to[e]);
    }
}

void cancle(int u) {
    colorCnt[color[u]]--;
    colorNum[colorCnt[color[u]] + 1]--;
    colorNum[colorCnt[color[u]]]++;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        cancle(to[e]);
    }
}

void dfs2(int u, int keep) {
    //先去轻儿子
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != son[u]) {
            dfs2(v, 0);
        }
    }

    //去 重儿子
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }

    //这个节点的贡献信息
    colorCnt[color[u]]++;
    colorNum[colorCnt[color[u]] - 1]--;
    colorNum[colorCnt[color[u]]]++;

    //回收轻儿子信息
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != son[u]) {
            effect(v);
        }
    }

    //判断以该节点为头的子树是不是符合题目要求
    //判断方式： 这个节点的颜色的出现次数 和 它这个颜色出现的次数相同的颜色个数  的乘积  和这个子树的节点个数比较
    //因为如果符合题目要求  那么所有颜色的出现次数都是一样的
    if (colorCnt[color[u]] * colorNum[colorCnt[color[u]]] == siz[u]) {
        ans++;
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
        cin >> color[i] >> father;
        if (i != 1) {
            addEdge(father, i);
        }
    }
    dfs1(1);
    dfs2(1, 0);
    cout << ans << "\n";
    return 0;
}