// 快递员，C++版
// 一共有n个节点，给定n-1条边，每条边给定边权，所有节点组成一棵树
// 对于点对(a, b)，假设你选择的中心点为x，那么点对的距离如下
// 点对(a, b)的距离 = a到x的路径权值和 + b到x的路径权值和
// 一共有m个点对，你需要选择中心点x，使得点对距离的最大值尽量小
// 打印这个最小的点对距离最大值
// 1 <= n、m <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4886
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题是重心移动型题目 可以认为是树上二分  因为每次移动确实可以减少一半
// 对于一个节点而言  查询以这个节点为中心的情况下  所有点对的答案
// 这其中的所有最大值点对中的点是不是都是来自于同一个子树
// 如果是  那么前往这个儿子节点可能会产生更好的答案  去这个儿子这里试试
// 否则没有更新的必要了
// 因为如果不是全部来自一个子树  那么无论中心点来到哪个子树中  答案一定会变得更大  因为这样会多走重复的路  最大值一定不会减少
// 如果来自同一个子树 那么前往这个子树的重心去继续操作 
// 这样最多移动logn次  这是重心的层数所决定的
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;
int a[MAXN];
int b[MAXN];

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int weight[MAXN << 1];
int cntg;

bool vis[MAXN];
int siz[MAXN];

// 记录在当前设置的中心点中  这个节点所属的父亲节点是哪个  判断是否来自同一个子树时用
int tree[MAXN];
int dist[MAXN];

void addEdge(int u, int v, int w) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    weight[cntg] = w;
    head[u] = cntg;
}

void getSize(int u, int fa) {
    siz[u] = 1;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
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
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
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

void dfs(int u, int fa, int d, int t) {
    tree[u] = t;
    dist[u] = d;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v != fa) {
            dfs(v, u, d + weight[e], t);
        }
    }
}

int compute() {
    int ans = 1000000001;
    int u = getCentroid(1, 0);
    while (!vis[u]) {
        // 不断跳往重心的过程
        vis[u] = true;
        tree[u] = u;
        dist[u] = 0;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            int w = weight[e];
            dfs(v, u, w, v);
        }
        // son表示目前的头结点中那个儿子可能有希望继续跳
        int maxDist = 0, son = 0;
        for (int i = 1; i <= m; i++) {
            int curDist = dist[a[i]] + dist[b[i]];
            int t1 = tree[a[i]];
            int t2 = tree[b[i]];
            if (maxDist < curDist) {
                maxDist = curDist;
                son = (t1 == t2) ? t1 : 0;
            } else if (maxDist == curDist && (t1 != t2 || t1 != son)) {
                son = 0;
            }
        }
        ans = min(ans, maxDist);
        if (son == 0) {
            break;
        }
        // 找到这个子树的重心
        u = getCentroid(son, u);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i];
    }
    cout << compute() << '\n';
    return 0;
}