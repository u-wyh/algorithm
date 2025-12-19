// 树上分块模版题，随机撒点，C++版
// 一共有n个节点，每个节点有点权，给定n-1条边，所有节点连成一棵树
// 接下来有m条操作，每条操作都要打印两个答案，描述如下
// 操作 k x1 y1 x2 y2 .. (一共k个点对) 
// 每个点对(x, y)，在树上都有从x到y的路径，那么k个点对就有k条路径
// 先打印k条路径上不同点权的数量，再打印点权集合中没有出现的最小非负数(mex)
// 1 <= n、点对总数 <= 10^5    点权 <= 30000
// 题目要求强制在线，具体规则可以打开测试链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P3603
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 随机撒点并不能被看成是严格的分块   只是设置了一些关键节点
// 通过随机性来保持时间复杂度
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXB = 401;
const int MAXV = 30001;
const int MAXP = 17;

int n, m, f, k;
int arr[MAXN];

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg;

// 树上倍增，就只是为了快速求出LCA
int dep[MAXN];
int stjump[MAXN][MAXP];

// 随机撒点
// markNum表示关键点数量
int markNum;
// vis[i]表示i号节点是否已经是关键点
bool vis[MAXN];
// markNode[k] = i 表示第k个关键点是编号为i的节点
int markNode[MAXN];
// kthMark[i] = k 表示i号节点是第k个关键点，kthMark[i] = 0 表示i号节点是非关键点
int kthMark[MAXN];
// up[i] = j，表示i号节点是关键点，它往上跳到最近的关键点是j号节点
int up[MAXN];
// downSet[k]的含义，路径是[第k个的关键点 .. 最近的上方关键点)，沿途所有节点值组成的位图
bitset<MAXV> downSet[MAXB];

bitset<MAXV> ans;

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

//建立倍增表
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXP; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e; e = nxt[e]) {
        if (to[e] != fa) {
            dfs(to[e], u);
        }
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    for (int p = MAXP - 1; p >= 0; p--) {
        if (dep[stjump[a][p]] >= dep[b]) {
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = MAXP - 1; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

//查询从x到xylca这条路上（不包括xylca）的所有点权的位图
void query(int x, int xylca) {
    //从起始点到第一个关键点  
    while (kthMark[x] == 0 && x != xylca) {
        ans[arr[x]] = 1;
        x = stjump[x][0];
    }
    //从第一个关键点到最后一个关键点
    while (up[x] && dep[up[x]] > dep[xylca]) {
        ans |= downSet[kthMark[x]];
        x = up[x];
    }
    //最后一个关键点到xylca
    while (x != xylca) {
        ans[arr[x]] = 1;
        x = stjump[x][0];
    }
}

void updateAns(int x, int y) {
    int xylca = lca(x, y);
    query(x, xylca);//x到xylca
    query(y, xylca);//y到xylca
    ans[arr[xylca]] = 1;//加上xylca
}

void prepare() {
    dfs(1, 0);
    int len = (int)sqrt(n * 10);
    markNum = (n + len - 1) / len;
    for (int b = 1, pick; b <= markNum; b++) {
        do {
            pick = rand() % n + 1;
        } while (vis[pick]);
        vis[pick] = true;
        markNode[b] = pick;
        kthMark[pick] = b;
    }
    for (int b = 1, cur; b <= markNum; b++) {
        downSet[b][arr[markNode[b]]] = 1;
        cur = stjump[markNode[b]][0];
        while (cur != 0) {
            if (kthMark[cur] > 0) {
                up[markNode[b]] = cur;
                break;
            } else {
                downSet[b][arr[cur]] = 1;
                cur = stjump[cur][0];
            }
        }
    }	
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    cin >> n >> m >> f;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    prepare();
    for (int i = 1, lastAns = 0; i <= m; i++) {
        ans.reset();
        cin >> k;
        for (int j = 1, x, y; j <= k; j++) {
            cin >> x >> y;
            if (f) {
                x ^= lastAns;
                y ^= lastAns;
            }
            updateAns(x, y);
        }
        int ans1 = ans.count();
        int ans2 = MAXV;
        for (int i = 0; i < MAXV; i++) {
            if (ans[i] == 0) {
                ans2 = i;
                break;
            }
        }
        cout << ans1 << ' ' << ans2 << '\n';
        lastAns = ans1 + ans2;
    }
    return 0;
}