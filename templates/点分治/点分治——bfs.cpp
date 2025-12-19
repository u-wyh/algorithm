// 首都，C++版
// 一共有n个节点，给定n-1条边，所有节点组成一棵树
// 给定长度为n的数组color，color[i]表示i号节点的颜色，颜色有k种
// 你需要在树上找到一个连通区，连通区内出现的每种颜色，在连通区外不存在
// 这样的连通区可能有多个，希望包含的颜色数量尽量少，打印(最少颜色数 - 1)的结果
// 1 <= n、k <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P7215
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 大思路是按照重心分治之后  每次查询这个节点的答案
// 计算这个节点的答案借助bfs完成  首先将这个节点放入队列中
// 每次弹出一个节点  将父亲节点放入（如果是当前的头结点就不用了）以及和自己颜色相同的节点
// 如果这些节点超出了目前子树的范围  那么结束  表示这个节点产生的答案一定不会是全局的答案
// 放入父亲节点（这里的父亲节点是以重心为根后建立的树的父亲）是为了找到一个更小的范围
// 放入同色节点是为了满足题目要求
// 为什么如果节点超出了范围  就返回无效值呢？
// 因为如果这个节点超出了当前的子树范围  那么这个颜色的节点之间联通至少要经过之前建立的重心
// 但是之前这个重心的答案不一定包含这个颜色  也就是说之前计算的答案一定不会比现在的更劣
// 这道题的关键就是想清楚为什么可以用点分治实现  只要想明白了  这道题也就不是太难了
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int INF = 1000000001;

int n, k;
int color[MAXN];

int headg[MAXN];
int nextg[MAXN << 1];
int tog[MAXN << 1];
int cntg;

// 颜色拥有的节点列表
int headc[MAXN];
int nextc[MAXN];
int toc[MAXN];
int cntc;

// 点分治
bool vis[MAXN];
int siz[MAXN];

// father[x] = y，表示x此时的父亲节点是y
int father[MAXN];
// nodeRoot[x] = y，表示x此时的重心是y
int nodeRoot[MAXN];

// 宽度优先遍历的队列
int que[MAXN];
// 节点是否进过队列
bool nodeVis[MAXN];
// 颜色是否讨论过
bool colorVis[MAXN];

void addEdge(int u, int v) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

void addNode(int color, int node) {
    nextc[++cntc] = headc[color];
    toc[cntc] = node;
    headc[color] = cntc;
}

void getSize(int u, int fa) {
    siz[u] = 1;
    for (int e = headg[u]; e; e = nextg[e]) {
        int v = tog[e];
        if (v != fa && !vis[v]) {
            getSize(v, u);
            siz[u] += siz[v];
        }
    }
}

int getCentroid(int u, int fa) {
    getSize(u, fa);
    int half = siz[u] >> 1;
    bool find = false;
    while (!find) {
        find = true;
        for (int e = headg[u]; e; e = nextg[e]) {
            int v = tog[e];
            if (v != fa && !vis[v] && siz[v] > half) {
                fa = u;
                u = v;
                find = false;
                break;
            }
        }
    }
    return u;
}

// 收集信息递归版
void dfs(int u, int fa, int rt) {
    father[u] = fa;
    nodeRoot[u] = rt;
    nodeVis[u] = false;
    colorVis[color[u]] = false;
    for (int e = headg[u]; e; e = nextg[e]) {
        int v = tog[e];
        if (v != fa && !vis[v]) {
            dfs(v, u, rt);
        }
    }
}

int calc(int u) {
    dfs(u, 0, u);
    int l = 1, r = 0;
    que[++r] = u;
    nodeVis[u] = true;
    int ans = 0;
    while (l <= r) {
        int cur = que[l++];
        if (cur != u && !nodeVis[father[cur]]) {
            que[++r] = father[cur];
            nodeVis[father[cur]] = true;
        }
        if (!colorVis[color[cur]]) {
            colorVis[color[cur]] = true;
            ans++;
            for (int e = headc[color[cur]]; e; e = nextc[e]) {
                int v = toc[e];
                // 超出目前的子树范围
                if (nodeRoot[v] != u) {
                    return INF;
                }
                if (!nodeVis[v]) {
                    que[++r] = v;
                    nodeVis[v] = true;
                }
            }
        }
    }
    return ans;
}

int solve(int u) {
    vis[u] = true;
    int ans = calc(u);
    for (int e = headg[u]; e; e = nextg[e]) {
        int v = tog[e];
        if (!vis[v]) {
            ans = min(ans, solve(getCentroid(v, u)));
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
        addNode(color[i], i);
    }
    int ans = solve(getCentroid(1, 0));
    cout << (ans - 1) << '\n';
    return 0;
}