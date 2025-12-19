// 王国和城市，C++版
// 一共有n个节点，给定n-1条无向边，所有节点组成一棵树
// 一共有q条查询，每条查询格式如下
// 查询 k a1 a2 ... ak : 给出了k个不同的重要点，其他点是非重要点
//                       你可以攻占非重要点，被攻占的点无法通行
//                       要让重要点两两之间不再连通，打印至少需要攻占几个非重要点
//                       如果攻占非重要点无法达成目标，打印-1
// 1 <= n、q <= 10^5
// 1 <= 所有查询给出的点的总数 <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF613D
// 测试链接 : https://codeforces.com/problemset/problem/613/D
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题主要是在虚树上进行树形dp  关键是转移关系
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXP = 20;

int n, q, k;

// 原始树
int headg[MAXN];
int nextg[MAXN << 1];
int tog[MAXN << 1];
int cntg;

// 虚树
int headv[MAXN];
int nextv[MAXN];
int tov[MAXN];
int cntv;

// 树上倍增求LCA + 生成dfn序
int dep[MAXN];
int dfn[MAXN];
int stjump[MAXN][MAXP];
int cntd;

// 关键点数组
int arr[MAXN];
// 标记节点是否是关键点
bool isKey[MAXN];

// 第一种建树方式
int tmp[MAXN << 1];
// 第二种建树方式
int stk[MAXN];

// 动态规划相关
// siz[u]，还有几个重要点没和u断开，值为0或者1
// cost[u]，表示节点u的子树中，做到不违规，至少需要攻占几个非重要点
int siz[MAXN];
int cost[MAXN];

bool cmp(int x, int y) {
    return dfn[x] < dfn[y];
}

// 原始树连边
void addEdgeG(int u, int v) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

// 虚树连边
void addEdgeV(int u, int v) {
    nextv[++cntv] = headv[u];
    tov[cntv] = v;
    headv[u] = cntv;
}

// 树上倍增的dfs过程
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = ++cntd;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXP; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = headg[u]; e; e = nextg[e]) {
        if (tog[e] != fa) {
            dfs(tog[e], u);
        }
    }
}

int getLca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    for (int p = MAXP - 1; p >= 0; p--) {
        if (dep[stjump[a][p]] >= dep[b]) a = stjump[a][p];
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

// 二次排序 + LCA连边的方式建立虚树
int buildVirtualTree1() {
    sort(arr + 1, arr + k + 1, cmp);
    int len = 0;
    for (int i = 1; i < k; i++) {
        tmp[++len] = arr[i];
        tmp[++len] = getLca(arr[i], arr[i + 1]);
    }
    tmp[++len] = arr[k];
    sort(tmp + 1, tmp + len + 1, cmp);
    int unique = 1;
    for (int i = 2; i <= len; i++) {
        if (tmp[unique] != tmp[i]) {
            tmp[++unique] = tmp[i];
        }
    }
    cntv = 0;
    // 清空用到的head数组
    for (int i = 1; i <= unique; i++) {
        headv[tmp[i]] = 0;
    }
    for (int i = 1; i < unique; i++) {
        addEdgeV(getLca(tmp[i], tmp[i + 1]), tmp[i + 1]);
    }
    return tmp[1];
}

// 单调栈的方式建立虚树
int buildVirtualTree2() {
    sort(arr + 1, arr + k + 1, cmp);
    cntv = 0;
    // 在入栈时清空连边
    headv[arr[1]] = 0;
    int top = 0;
    stk[++top] = arr[1];
    for (int i = 2; i <= k; i++) {
        int x = arr[i];
        int y = stk[top];
        int lca = getLca(x, y);
        while (top > 1 && dfn[stk[top - 1]] >= dfn[lca]) {
            addEdgeV(stk[top - 1], stk[top]);
            top--;
        }
        if (lca != stk[top]) {
            headv[lca] = 0;
            addEdgeV(lca, stk[top]);
            // 这里是换顶  完整的应该是top-- stk[top++]=lca
            stk[top] = lca;
        }
        headv[x] = 0;
        stk[++top] = x;
    }
    while (top > 1) {
        addEdgeV(stk[top - 1], stk[top]);
        top--;
    }
    return stk[1];
}

// 树型dp的过程
void dp(int u) {
    cost[u] = siz[u] = 0;
    for (int e = headv[u]; e; e = nextv[e]) {
        int v = tov[e];
        dp(v);
        cost[u] += cost[v];
        siz[u] += siz[v];
    }
    if (isKey[u]) {
        // 如果这个节点是关键点  那么将它和他的孩子（孩子的子树中也存在重要点）之间的边全部断开
        // 肯定可以断开 因为如果两个重要的相连  那么直接就是不行的
        // 那么代价就是这些孩子节点的数量  可以用sz[u]保存
        cost[u] += siz[u];
        siz[u] = 1;
    } else if (siz[u] > 1) {
        // 如果不是关键点 并且子树中至少有两个以上的关键点没有处理
        // 那么这个点牺牲掉  从而使子树中的重要点不联通
        cost[u]++;
        siz[u] = 0;
    }
    // 剩下的情况是不是关键点  子树中只有一个没有处理的重要点  那么交给父亲处理肯定不劣
}

int compute() {
    // 节点标记关键点信息
    for (int i = 1; i <= k; i++) {
        isKey[arr[i]] = true;
    }
    bool check = true;
    for (int i = 1; i <= k; i++) {
        // 只能通过攻占非关键点的方式，来隔开关键点
		// 所以如果 a 和 a的父节点 都是关键点，这是怎么也隔不开的
		// 直接返回-1即可
        if (isKey[stjump[arr[i]][0]]) {
            check = false;
            break;
        }
    }
    int ans = -1;
    if (check) {
        int tree = buildVirtualTree1();
        // int tree = buildVirtualTree2();
        dp(tree);
        ans = cost[tree];
    }
    // 节点撤销关键点信息
    for (int i = 1; i <= k; i++) {
        isKey[arr[i]] = false;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdgeG(u, v);
        addEdgeG(v, u);
    }
    dfs(1, 0);
    cin >> q;
    for (int t = 1; t <= q; t++) {
        cin >> k;
        for (int i = 1; i <= k; i++) {
            cin >> arr[i];
        }
        cout << compute() << '\n';
    }
    return 0;
}