// 用途：统计带权树上距离不超过 k 的无序点对，不把 (x,x) 算作点对。
// 时间：O(n log² n)，每层点分治都要排序后用双指针计数。
// 空间：O(n)。
// 注意：边权非负，才能剪掉到重心距离已经超过 k 的分支。
// 例题：https://www.luogu.com.cn/problem/P4178
// 题意：给定一棵树和 k，求距离≤k 的不同节点对数量。
// 思路：先算当前连通块所有点对，再减去每个子树内部的点对，留下路径经过重心的贡献。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50001;

int n, k;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int weight[MAXN << 1];
int cntg;

bool vis[MAXN];
int siz[MAXN];
int order[MAXN], parentNode[MAXN];
int stackNode[MAXN], stackParent[MAXN], stackDist[MAXN];

int disArr[MAXN];
int cnta;

void addEdge(int u, int v, int w) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    weight[cntg] = w;
    head[u] = cntg;
}

void getSize(int u, int fa) {
    // 连通块可能是一条 4 万点长链，显式记录 DFS 顺序以免递归栈溢出。
    int count = 1;
    order[0] = u;
    parentNode[u] = fa;
    for (int i = 0; i < count; ++i) {
        int x = order[i];
        for (int e = head[x]; e; e = nxt[e]) {
            int v = to[e];
            if (v != parentNode[x] && !vis[v]) {
                parentNode[v] = x;
                order[count++] = v;
            }
        }
    }
    for (int i = count - 1; i >= 0; --i) {
        int x = order[i];
        siz[x] = 1;
        for (int e = head[x]; e; e = nxt[e]) {
            int v = to[e];
            if (v != parentNode[x] && !vis[v]) siz[x] += siz[v];
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

void dfs(int u, int fa, int dis) {
    int top = 0;
    stackNode[top] = u;
    stackParent[top] = fa;
    stackDist[top++] = dis;
    while (top) {
        --top;
        int x = stackNode[top], p = stackParent[top], d = stackDist[top];
        if (d > k) continue;
        disArr[++cnta] = d;
        for (int e = head[x]; e; e = nxt[e]) {
            int v = to[e];
            if (v != p && !vis[v]) {
                stackNode[top] = v;
                stackParent[top] = x;
                stackDist[top++] = d + weight[e];
            }
        }
    }
}

long long calc(int u, int dis) {
    cnta = 0;
    dfs(u, 0, dis);
    long long ans = 0;
    sort(disArr + 1, disArr + cnta + 1);
    // 双指针统计距离和≤k 的无序点对；不包括同一点。
    for (int l = 1, r = cnta; l <= r; ) {
        if (disArr[l] + disArr[r] <= k) {
            ans += r - l;
            l++;
        } else {
            r--;
        }
    }
    return ans;
}

long long solve(int u) {
    vis[u] = true;
    long long ans = calc(u, 0); // 先计当前连通块的全部点对。
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) {
            ans -= calc(v, weight[e]); // 同一子树内的路径不经过重心，先扣掉。
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
    cin >> k;
    cout << solve(getCentroid(1, 0)) << '\n';
    return 0;
}
