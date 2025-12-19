// https://www.luogu.com.cn/problem/P5025
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500003;       // 最大炸弹数量
const int MAXM = 2000003;      // 最大线段树节点数（4倍空间）
const long long INF = 0x3f3f3f3f3f3f3f3fLL;  // 无穷大值
const int MOD = 1000000007;    // 模数

long long pos[MAXN];           // 炸弹坐标数组
long long len[MAXN];           // 炸弹爆炸半径数组
int l[MAXN];             // 炸弹爆炸范围左边界（炸弹编号）
int r[MAXN];             // 炸弹爆炸范围右边界（炸弹编号）
int n;                         // 炸弹数量

// 线段树节点结构
struct Node {
    int l, r;                  // 节点表示的区间[l, r]
    Node(int l = 0, int r = 0) : l(l), r(r) {}
};

vector<int> adj[MAXM];         // 原图的邻接表
vector<int> scc_adj[MAXM];     // 强连通分量图的邻接表
Node tree[MAXM];               // 线段树节点数组
int id[MAXN];                  // 每个炸弹对应的线段树叶子节点ID
int nodecnt;                   // 线段树节点计数
int dfn[MAXM], low[MAXM];      // Tarjan算法用到的dfn和low数组
int dfncnt;                    // DFS计数器（用于Tarjan）
int stk[MAXM];                 // Tarjan算法栈
int top;                       // 栈顶指针
bool inStack[MAXM];            // 节点是否在栈中
int col[MAXM];                 // 节点所属的强连通分量编号
int color;                     // 强连通分量计数器
int collt[MAXM];               // 强连通分量能达到的最左炸弹编号
int colrt[MAXM];               // 强连通分量能达到的最右炸弹编号
bool vis[MAXM];                // DFS访问标记

// 二分查找：找到第一个坐标≥val的炸弹位置
int find_left(long long val) {
    int l = 1, r = n, ans = 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (pos[mid] >= val) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

// 二分查找：找到最后一个坐标≤val的炸弹位置
int find_right(long long val) {
    int l = 1, r = n, ans = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (pos[mid] <= val) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

// 构建线段树
void build(int l, int r, int i) {
    tree[i] = Node(l, r);      // 初始化节点
    nodecnt = max(nodecnt, i); // 更新最大节点编号
    
    // 叶子节点：存储炸弹ID
    if (l == r) {
        id[l] = i;             // 记录炸弹对应的线段树节点
        return;
    }
    
    int mid = (l + r) >> 1;
    // 递归构建左右子树
    build(l, mid, i << 1);          // 左子树
    build(mid + 1, r, (i << 1) | 1); // 右子树
    
    // 添加线段树内部边：父节点指向子节点
    adj[i].push_back(i << 1);        // 左子节点
    adj[i].push_back((i << 1) | 1);  // 右子节点
}

// 线段树优化建图：将节点u与覆盖区间[L, R]的线段树节点连接
void connect(int u, int L, int R, int l, int r, int idx) {
    // 当前线段树节点区间[l, r]完全包含在目标区间[L, R]中
    if (L <= l && r <= R) {
        if (u != idx) {        // 避免自环
            adj[u].push_back(idx); // 添加边
        }
        return;
    }
    
    int mid = (l + r) >> 1;  // 区间中点
    // 递归处理左右子树
    if (L <= mid) connect(u, L, R, l, mid, idx << 1);
    if (R > mid) connect(u, L, R, mid + 1, r, (idx << 1) | 1);
}

// Tarjan算法求强连通分量
void tarjan(int u) {
    dfn[u] = low[u] = ++dfncnt; // 初始化dfn和low
    stk[++top] = u;             // 节点入栈
    inStack[u] = true;          // 标记节点在栈中
    
    // 遍历所有邻接节点
    for (int v : adj[u]) {
        if (!dfn[v]) {          // 未访问过的节点
            tarjan(v);
            low[u] = min(low[u], low[v]); // 更新low值
        } else if (inStack[v]) { // 已在栈中的节点（后向边）
            low[u] = min(low[u], dfn[v]); // 更新low值
        }
    }
    
    // 发现强连通分量的根节点
    if (low[u] == dfn[u]) {
        color++;  // 增加强连通分量计数
        int v;
        do {
            v = stk[top--];     // 弹出栈顶节点
            inStack[v] = false;  // 标记不在栈中
            col[v] = color;      // 着色，标记所属强连通分量
            // 更新当前强连通分量的左右边界
            collt[color] = min(collt[color], tree[v].l);
            colrt[color] = max(colrt[color], tree[v].r);
        } while (v != u);  // 直到处理到当前节点
    }
}

// 在强连通分量图上DFS，传递区间信息
void dfs(int u) {
    vis[u] = true;
    for (int v : scc_adj[u]) {  // 遍历所有邻接强连通分量
        if (!vis[v]) {
            dfs(v);  // 递归DFS
        }
        // 更新当前强连通分量的左右边界
        collt[u] = min(collt[u], collt[v]);
        colrt[u] = max(colrt[u], colrt[v]);
    }
}

int main() {
    // 读入炸弹数量
    scanf("%d", &n);
    // 读入每个炸弹的坐标和爆炸半径
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &pos[i], &len[i]);
    }
    
    // 构建线段树，根节点为1，区间[1, n]
    build(1, n, 1);
    
    // 计算每个炸弹的爆炸范围
    for (int i = 1; i <= n; ++i) {
        if (len[i] == 0) continue;  // 爆炸半径为0，跳过
        
        // 计算炸弹i的爆炸范围[L, R]
        l[i] = find_left(pos[i] - len[i]);   // 左边界
        r[i] = find_right(pos[i] + len[i]);  // 右边界
        
        // 将炸弹i对应的节点与覆盖[L, R]的线段树节点连接
        connect(id[i], l[i], r[i], 1, n, 1);
    }
    
    // 对整个图（线段树）运行Tarjan算法求强连通分量
    for (int i = 1; i <= nodecnt; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    
    // 构建强连通分量图
    for (int u = 1; u <= nodecnt; ++u) {
        for (int v : adj[u]) {
            // 如果u和v属于不同的强连通分量
            if (col[u] != col[v]) {
                // 添加从u的强连通分量指向v的强连通分量的边
                scc_adj[col[u]].push_back(col[v]);
            }
        }
    }
    
    // 对每个强连通分量的邻接表去重
    for (int i = 1; i <= color; ++i) {
        sort(scc_adj[i].begin(), scc_adj[i].end());
        scc_adj[i].erase(unique(scc_adj[i].begin(), scc_adj[i].end()), scc_adj[i].end());
    }
    
    // 在强连通分量图上DFS，传递区间信息
    for (int i = 1; i <= color; ++i) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    
    // 计算最终答案
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        // 获取炸弹i对应的强连通分量
        int u = col[id[i]];
        // 计算该炸弹能引爆的炸弹数量
        int count = colrt[u] - collt[u] + 1;
        // 累加答案：i * 引爆数量
        ans = (ans + (long long)i * count) % MOD;
    }
    
    // 输出答案
    printf("%lld\n", ans);
    return 0;
}