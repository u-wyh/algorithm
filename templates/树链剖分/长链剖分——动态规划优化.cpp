// 火热旅馆，C++版
// 一共有n个节点，给定n-1条边，所有节点连成一棵树
// 三个点构成一个点组(a, b, c)，打乱顺序认为是同一个点组
// 求树上有多少点组，内部任意两个节点之间的距离是一样的
// 1 <= n <= 10^5
// 答案一定在long类型范围内
// 测试链接 : https://www.luogu.com.cn/problem/P5904
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg;

int fa[MAXN];
int son[MAXN];
int len[MAXN];
int cntd;

// 动态规划
// 每个点在动态规划表f中的开始位置，就是dfn序
int fid[MAXN];
// 每个点在动态规划表g中的开始位置，课上讲的设计
int gid[MAXN];

// 不同的更新方式对应不同的设置id编号
// f[i][j]的含义是i为头的子树上 到达他的距离为j个点的个数
// 动态规划表f，f[父][i]依赖f[子][i-1]
long long f[MAXN];
// g[u][i]的含义是以u为头的子树上  x和y到达他们的lca（设为z）的距离满足
// x到z的距离  ==   y到z的距离   ==   z到u的距离+j
// 动态规划表g，g[父][i]依赖g[子][i+1]
long long g[MAXN << 1];
long long ans;

void setf(int u, int i, long long v) {
    f[fid[u] + i] = v;
}

long long getf(int u, int i) {
    return f[fid[u] + i];
}

void setg(int u, int i, long long v) {
    g[gid[u] + i] = v;
}

long long getg(int u, int i) {
    return g[gid[u] + i];
}

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs1(int u, int f) {
    fa[u] = f;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            if (son[u] == 0 || len[son[u]] < len[v]) {
                son[u] = v;
            }
        }
    }
    len[u] = len[son[u]] + 1;
}

// 给每个节点分配fid和gid
// gid的编号分配规则是长链的最后一个节点的编号是这条长链的二倍  
// 长链上的节点的编号是自己儿子的编号+1  这样可以保证没有重叠  或许有少量的浪费
void dfs2(int u, int top) {
    fid[u] = cntd++;
    if (son[u] == 0) {
        gid[u] = fid[top] * 2;
        return;
    }
    dfs2(son[u], top);
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != son[u] && v != fa[u]) {
            dfs2(v, v);
        }
    }
    gid[u] = gid[son[u]] + 1;
}

// 计算每个节点的f信息和g信息，同时统计答案
// 统计以u为头的子树的答案  其中不能包括u的子节点的子树的答案（也就是说三个点不能同时出现在一个子节点的子树中）
// 那么这三个节点一定会和u产生关系  要么u就是节点之一  要么三个点之间的路径肯定跨过了u
// 情况1很简单  就是g[u][0]  这里需要等到所有子树的信息收集完毕了在统计
// 情况2的时候  需要在加入一个子树的时候 统计部分答案  就是树形dp最初的形式
void dfs3(int u) {
    setf(u, 0, 1);
    if (son[u] == 0) {
        return;
    }
    dfs3(son[u]);
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != son[u] && v != fa[u]) {
            dfs3(v);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != son[u] && v != fa[u]) {
            // 情况2，u树上，选择三个点，u没被选中，但跨u选点
            for (int i = 0; i <= len[v]; i++) {
                // 情况2的分支一，之前遍历的子树里选两个点，当前子树里选一个点
                if (i < len[u] && i - 1 >= 0) {
                    ans += getg(u, i) * getf(v, i - 1);
                }
                // 情况2的分支二，之前遍历的子树里选一个点，当前子树里选两个点
                // 这里i>0  是因为不能是u
                if (i > 0 && i + 1 < len[v]) {
                    ans += getf(u, i) * getg(v, i + 1);
                }
            }
            // 更新g数组
            for (int i = 0; i <= len[v]; i++) {
                if (i + 1 < len[v]) {
                    // g[u][i]=g[u][i]+g[v][i+1]  表示新加的全部是在v子树中
                    setg(u, i, getg(u, i) + getg(v, i + 1));
                }
                if (i - 1 >= 0) {
                    // g[u][i]=g[u][i]+f[u][i]*f[v][i-1]  表示的是一个节点是来自v
                    setg(u, i, getg(u, i) + getf(u, i) * getf(v, i - 1));
                }
            }
            // 更新f数组
            for (int i = 0; i <= len[v]; i++) {
                if (i - 1 >= 0) {
                    setf(u, i, getf(u, i) + getf(v, i - 1));
                }
            }
        }
    }
    // 情况1，u树上，选择三个点，u被选中
    ans += getg(u, 0);
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
    dfs2(1, 1);
    dfs3(1);
    cout << ans << "\n";
    return 0;
}