// 用途：离线处理边的添加、删除和两点是否连通的查询。
// 时间：O((n+q)log q log n)。
// 空间：O(n²+q log q)，邻接端点的上次出现时间用 n×n 数组记录。
// 注意：可撤销并查集不能路径压缩；任务只存加边操作编号，避免复制端点。
// 例题：https://loj.ac/p/121
// 题意：边可增删，多次询问两点当前是否连通。
// 思路：边的生存期挂在线段树节点，DFS 时合并并查集，回溯时撤销。
#include <bits/stdc++.h>
using namespace std;
// 点的数量最大值
const int MAXN = 5001;
// 操作数量最大值
const int MAXM = 500001;
// 一条边的生存区间最多挂 O(log m) 个节点，总任务上界按 m log m 开。
const int MAXT = MAXM * 20;

int n, m;

// 操作类型op、端点u、端点v
int op[MAXM];
int u[MAXM];
int v[MAXM];

// last[x][y] : 点x和点y的边，上次出现的时间点
int last[MAXN][MAXN];

// 可撤销并查集
int father[MAXN];
int siz[MAXN];
int rollback[MAXN][2];
int opsize = 0;

// 线段树每个区间拥有哪些任务的列表，链式前向星表示
int head[MAXM << 2];
int nxt[MAXT];
int taskOp[MAXT]; // 原加边操作编号；端点从 u/v 数组读取。
int cnt = 0;

// ans[i]为第i条操作的答案，只有查询操作才有答案
bool ans[MAXM];

void addEdge(int i, int edgeOp) {
    nxt[++cnt] = head[i];
    taskOp[cnt] = edgeOp;
    head[i] = cnt;
}

//可撤销并查集  没有扁平化操作
int find(int i) {
    while (i != father[i]) {
        i = father[i];
    }
    return i;
}

// 必须要小挂大 不然时间复杂度会达到O(n)级别
void Union(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (siz[fx] < siz[fy]) {
        int tmp = fx;
        fx = fy;
        fy = tmp;
    }
    father[fy] = fx;
    siz[fx] += siz[fy];
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
    int fx = rollback[opsize][0];
    int fy = rollback[opsize--][1];
    father[fy] = fy;
    siz[fx] -= siz[fy];
}

// 把加边操作挂到边存在的时间区间 [jobl, jobr]。
void add(int jobl, int jobr, int edgeOp, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addEdge(i, edgeOp);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, edgeOp, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, edgeOp, mid + 1, r, i << 1 | 1);
        }
    }
}

//dfs遍历树
void dfs(int l, int r, int i) {
    int unionCnt = 0;//记录这个节点上进行了多少次合并操作  方便最后的撤销操作
    for (int ei = head[i], x, y, fx, fy; ei > 0; ei = nxt[ei]) {
        x = u[taskOp[ei]];
        y = v[taskOp[ei]];
        fx = find(x);
        fy = find(y);
        if (fx != fy) {
            Union(fx, fy);
            unionCnt++;
        }
    }
    if (l == r) {
        //在每个叶节点统计答案 
        if (op[l] == 2) {
            ans[l] = find(u[l]) == find(v[l]);
        }
    } else {
        int mid = (l + r) >> 1;
        dfs(l, mid, i << 1);
        dfs(mid + 1, r, i << 1 | 1);
    }
    for (int j = 1; j <= unionCnt; j++) {
        undo();
    }
}

//整理所有的信息
void prepare() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        siz[i] = 1;
    }
    for (int i = 1, t, x, y; i <= m; i++) {
        t = op[i];
        x = u[i];
        y = v[i];
        if (t == 0) {
            //如果是连线
            last[x][y] = i;
        } else if (t == 1) {
            //如果是删除边  那么就是意味着在 last~i-1 这个时间段内 x和y存在边的关系
            add(last[x][y], i - 1, last[x][y], 1, m, 1);
            last[x][y] = 0;
        }
    }
    for (int x = 1; x <= n; x++) {
        for (int y = x + 1; y <= n; y++) {
            //表示直到最后还没有被删除的边  说明他们从最后一个加入开始一直生效到最后
            if (last[x][y] != 0) {
                add(last[x][y], m, last[x][y], 1, m, 1);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, t, x, y; i <= m; i++) {
        cin >> t >> x >> y;
        op[i] = t;
        u[i] = min(x, y);
        v[i] = max(x, y);
    }
    prepare();
    dfs(1, m, 1);
    for (int i = 1; i <= m; i++) {
        if (op[i] == 2) {
            if (ans[i]) {
                cout << "Y" << "\n";
            } else {
                cout << "N" << "\n";
            }
        }
    }
   return 0;
}
