// 主导颜色累加和，C++版
// 一共有n个节点，编号1~n，给定n-1条边，所有节点连成一棵树，1号节点为树头
// 每个节点给定一种颜色值，主导颜色累加和定义如下
// 以x为头的子树上，哪种颜色出现最多，那种颜色就是主导颜色，主导颜色可能不止一种
// 所有主导颜色的值累加起来，每个主导颜色只累加一次，就是该子树的主导颜色累加和
// 打印1~n每个节点为头的子树的主导颜色累加和
// 1 <= n、颜色值 <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF600E
// 测试链接 : https://codeforces.com/problemset/problem/600/E
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题的大思路是统计每个节点最多出现次数的次数是多少 如果当前出现的一个颜色次数等于这个值 那么答案相加
// 如果大于这个值  那么就是更新答案
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n;
int color[MAXN];//节点颜色信息

//链式前向星建图
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cnt = 0;

//重链剖分
int fa[MAXN];
int siz[MAXN];
int son[MAXN];

//表示不同颜色出现的次数
int colorCnt[MAXN];
//表示目前出现的次数最多的颜色出现了多少次
int maxCnt[MAXN];
//记录当前节点的答案
long long ans[MAXN];

void addEdge(int u, int v) {
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

//重链剖分 统计重儿子信息
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

void effect(int u, int h) {
    //这个函数多一个参数h 表示收集到的信息要传递给h节点
    colorCnt[color[u]]++;
    if (colorCnt[color[u]] == maxCnt[h]) {
        //如果出现次数都是最多的 那么答案累加
        ans[h] += color[u];
    } else if (colorCnt[color[u]] > maxCnt[h]) {
        //如果出现次数更多 那么更新答案
        maxCnt[h] = colorCnt[color[u]];
        ans[h] = color[u];
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u]) {
            effect(v, h);
        }
    }
}

//取消轻儿子的影响
void cancle(int u) {
    colorCnt[color[u]] = 0;
    maxCnt[u] = 0;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u]) {
            cancle(v);
        }
    }
}

void dfs2(int u, int keep) {
    //先去轻儿子
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            dfs2(v, 0);
        }
    }
    //再去重儿子
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    //整理当前节点的贡献
    //首先继承重儿子的信息
    maxCnt[u] = maxCnt[son[u]];
    ans[u] = ans[son[u]];

    colorCnt[color[u]]++;//该节点的颜色数量加一
    //更新主导颜色
    if (colorCnt[color[u]] == maxCnt[u]) {
        ans[u] += color[u];
    } else if (colorCnt[color[u]] > maxCnt[u]) {
        maxCnt[u] = colorCnt[color[u]];
        ans[u] = color[u];
    }

    //回收轻儿子信息
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            effect(v, u);//这个地方要注意多一个参数u
        }
    }
    if (keep == 0) {
        cancle(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;
}