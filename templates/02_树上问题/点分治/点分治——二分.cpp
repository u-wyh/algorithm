// 最大中位数路径，C++版
// 一共有n个节点，给定n-1条边，每条边给定边权，所有节点组成一棵树
// 一条简单路径上，收集所有边权组成序列，其中的 下中位数 作为路径的权
// 边数在[limitl, limitr]范围的所有路径中，找到最大权的路径
// 如果有多条路径，找到其中一个方案即可，打印两个端点
// 1 <= n <= 10^5    0 <= 边权 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/CF150E
// 测试链接 : https://codeforces.com/problemset/problem/150/E
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题二分的思路是二分答案  子树中的每条边如果权值大于这个候选值 那么权值为1  否则为-1
// 然后根据已经访问过的信息和现在正在访问的信息判断答案是否可以满足
// 这里不能使用线段树  否则时间复杂度会超时
// 这里用的是单调队列维护窗口的最大值
// 这里排序的时候必须要用到按秩排序  因为每次新来的子树需要借助之前的信息来完成更新答案
// 如果一个子树的大小是k  那么这样可能导致的已更新的表长度最多是k长度
// 那么之前的树最大也不会超过k  也就是之前的表最大也不会超过k长度
// 那么每个新加入的子树的时间复杂度最多就是O(k)  这样加起来就是O(n)级别  符合点分治的要求
// 总的时间复杂度是O(n*log(n)*log(n))  二分log(n)  点分治n*log(n)
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int INF = 1000000001;

int n, limitl, limitr, cntw;

// 端点u、端点v、边权w
struct Input {
    int u, v, w;
};

bool InputCmp(Input a, Input b) {
    return a.w < b.w;
}

Input arr[MAXN];

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int weight[MAXN << 1];
int cntg;

bool vis[MAXN];
int siz[MAXN];

// 边的编号eid、边连接的子树大小size  用于按秩排序
struct Edge {
    int eid, size;
};

bool EdgeCmp(Edge a, Edge b) {
    return a.size < b.size;
}

Edge edgeArr[MAXN];
int cnte;

int preVal[MAXN];
int preNode[MAXN];
int preLen;

int curVal[MAXN];
int curNode[MAXN];
int curLen;

int que[MAXN];

int ans, ansu, ansv;

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

void dfs(int u, int fa, int edge, int sum, int limit) {
    curLen = max(curLen, edge);
    if (sum > curVal[edge]) {
        curVal[edge] = sum;
        curNode[edge] = u;
    }
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        int w = weight[e];
        if (v != fa && !vis[v]) {
            dfs(v, u, edge + 1, sum + (w >= limit ? 1 : -1), limit);
        }
    }
}

bool check(int u, int limit) {
    preVal[0] = 0;
    preNode[0] = u;
    preLen = 0;
    for (int k = 1; k <= cnte; k++) {
        int v = to[edgeArr[k].eid];
        int w = weight[edgeArr[k].eid];
        for (int i = 1; i <= siz[v]; i++) {
            curVal[i] = -INF;
        }
        curLen = 0;

        dfs(v, u, 1, w >= limit ? 1 : -1, limit);

        int ql = 1, qr = 0;
        // 根据之前的信息，初步建立窗口，子树按秩处理非常重要
        for (int i = min(preLen, limitr); i >= limitl; i--) {
            while (ql <= qr && preVal[que[qr]] <= preVal[i]) {
                qr--;
            }
            que[++qr] = i;
        }

        int down = limitr, up = limitl;
        for (int i = 1; i <= curLen; i++) {
            up--;
            if (up >= 0 && up <= preLen) {
                while (ql <= qr && preVal[que[qr]] <= preVal[up]) {
                    qr--;
                }
                que[++qr] = up;
            }
            // 顶多将队列中第一个的删除  并且这个位置必须是down
            if (ql <= qr && que[ql] == down) {
                ql++;
            }
            down--;
            if (ql <= qr && preVal[que[ql]] + curVal[i] >= 0) {
                if (limit > ans) {
                    ans = limit;
                    ansu = curNode[i];
                    ansv = preNode[que[ql]];
                }
                return true;
            }
        }

        // 将本次新加的用于更新已访问过的
        for (int i = 1; i <= curLen; i++) {
            if (i > preLen || curVal[i] > preVal[i]) {
                preVal[i] = curVal[i];
                preNode[i] = curNode[i];
            }
        }
        // 更新已访问过的可能用于答案的最大长度
        preLen = max(preLen, curLen);
    }
    return false;
}

void calc(int u) {
    // 这里重新要getsize一下  目的是我们要按秩排序
    // 目的是为了保证时间复杂度不会爆炸
    getSize(u, 0);
    cnte = 0;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) {
            edgeArr[++cnte] = { e, siz[v] };
        }
    }
    sort(edgeArr + 1, edgeArr + cnte + 1, EdgeCmp);
    int l = 1, r = cntw, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(u, mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
        if (r <= ans) break;
    }
}

void solve(int u) {
    vis[u] = true;
    calc(u);
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) {
            solve(getCentroid(v, u));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> limitl >> limitr;
    for (int i = 1; i < n; i++) {
        cin >> arr[i].u >> arr[i].v >> arr[i].w;
    }
    // 边按照边权排序  实现离散化
    sort(arr + 1, arr + n, InputCmp);
    cntw = 0;
    for (int i = 1; i < n; i++) {
        if (i == 1 || arr[i - 1].w != arr[i].w) {
            cntw++;
        }
        addEdge(arr[i].u, arr[i].v, cntw);
        addEdge(arr[i].v, arr[i].u, cntw);
    }
    solve(getCentroid(1, 0));
    cout << ansu << " " << ansv << '\n';
    return 0;
}