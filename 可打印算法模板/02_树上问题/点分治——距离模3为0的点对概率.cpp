// 用途：统计树上距离为 3 的倍数的有序点对，并输出其概率。
// 时间：O(n log n)。
// 空间：O(n)。
// 例题：https://www.luogu.com.cn/problem/P2634
// 题意：求树上随机有序点对距离为 3 的倍数的概率。
// 思路：按重心拆分，统计到重心距离的模 3 余数并排除同子树点对。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20001;

int n;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int weight[MAXN << 1];
int cntg;

// vis[u] = true，表示u是之前的分治点
bool vis[MAXN];
int siz[MAXN];

// cur[v]，表示往下走的当前路径中，路径权值和 % 3 == v的路径有多少条
// all[v]，表示往下走的所有路径中，路径权值和 % 3 == v的路径有多少条
int cur[3];
int all[3];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

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

// 找到u子树的重心
int getCentroid(int u, int fa) {
    getSize(u, fa);
    int half = siz[u] >> 1;
    bool find = false;
    while (!find) {
        find = true;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v != fa && !vis[v] && siz[v] > half) {
                // 如果v子树大小大于u整个子树大小的一半  那说明重心就是在v的子树中
                fa = u;
                u = v;
                find = false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u, int fa, int dis) {
    cur[dis % 3]++;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v != fa && !vis[v]) {
            dfs(v, u, dis + weight[e]);
        }
    }
}

int calc(int u) {
    int ans = 1;// 这个初始为1 因为头结点自己也是一个符合条件的答案
    all[0] = all[1] = all[2] = 0;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        int w = weight[e];
        if (!vis[v]) {
            cur[0] = cur[1] = cur[2] = 0;
            // 注意这里遍历的是他的子树  收集到的cur信息全部是到u的距离
            dfs(v, u, w);
            ans += all[0] * cur[0] * 2 + all[1] * cur[2] * 2 + all[2] * cur[1] * 2 + cur[0] * 2;
            all[0] += cur[0];
            all[1] += cur[1];
            all[2] += cur[2];
        }
    }
    return ans;
}

int solve(int u) {
    int ans = 0;
    vis[u] = true;
    // 计算以u为重心（同时也是头结点）的答案
    ans += calc(u);
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) {
            // 遍历每个子树的重心  去重心解决问题
            // 同时避免走回头路（即访问到已经访问的节点）
            ans += solve(getCentroid(v, u));
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    int centroid = getCentroid(1, 0);
    int a = solve(centroid);
    int b = n * n;
    int c = gcd(a, b);
    a /= c;
    b /= c;
    cout << a << "/" << b << '\n';
    return 0;
}
