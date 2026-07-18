// 接水果，C++版
// 一共有n个点，给定n-1条无向边，所有点连成一棵树
// 一共有p个盘子，每个盘子格式 a b c : 盘子是点a到点b的路径，盘子权值为c
// 一共有q个水果，每个水果格式 u v k : 水果是点u到点v的路径，k含义如下
// 如果一个盘子路径完全在一个水果路径的内部，那么该盘子可以接住该水果
// 那么对于每个水果，可能有很多盘子都可以将其接住，打印其中第k小的权值
// 1 <= n、p、q <= 4 * 10^4
// 0 <= 盘子权值 <= 10^9
// 内存可用空间500MB
// 测试链接 : https://www.luogu.com.cn/problem/P3242
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 40001;
const int MAXH = 16;
const int INF = 1000000001;

struct Event {
   int op, x, yl, yr, v, y, k, i;
};

bool EventCmp(Event e1, Event e2) {
   if (e1.x != e2.x) {
       return e1.x < e2.x;
   }
   return e1.op < e2.op;
}

int n, p, q;

// 链式前向星建图
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 0;

// 树上倍增 + 每棵子树上的ldfn和rdfn
int dep[MAXN];
int ldfn[MAXN];//这个子树上dfn序最小值
int rdfn[MAXN];//这个子树上dfn序最大值
int stjump[MAXN][MAXH];
int cntd = 0;

// 只有y维度的树状数组
int tree[MAXN];

// 所有事件排完序之后，依次把下标放入eid数组
int eid[MAXN << 3];
// 每个事件有8个属性值
// op==1加盘子，x处加、yl、yr，盘子权值v、空缺、空缺、空缺
// op==2删盘子，x处删、yl、yr，盘子权值v、空缺、空缺、空缺
// op==3为水果，x、空缺、空缺、空缺、y、要求k、问题编号i
Event event[MAXN << 3];
// 事件的总数
int cnte = 0;

// 整体二分
int lset[MAXN << 3];
int rset[MAXN << 3];

// 每个水果的答案
int ans[MAXN];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    ldfn[u] = ++cntd;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        if (to[e] != fa) {
            dfs(to[e], u);
        }
    }
    rdfn[u] = cntd;
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (dep[stjump[a][p]] >= dep[b]) {
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

// 已知a和b的最低公共祖先一定是a或b
// 假设祖先为x，后代为y，返回x的哪个儿子的子树里有y
int lcaSon(int a, int b) {
    if (dep[a] < dep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (dep[stjump[a][p]] > dep[b]) {
            a = stjump[a][p];
        }
    }
    return a;
}

int lowbit(int i) {
    return i & -i;
}

void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

// 树状数组中[l..r]范围上的每个数增加v  差分数组
void add(int l, int r, int v) {
    add(l, v);
    add(r + 1, -v);
}

// 树状数组中查询单点的值
int query(int i) {
    int ret = 0;
    while (i > 0) {
        ret += tree[i];
        i -= lowbit(i);
    }
    return ret;
}

void addPlate(int x, int yl, int yr, int v) {
    event[++cnte].op = 1;
    event[cnte].x = x;
    event[cnte].yl = yl;
    event[cnte].yr = yr;
    event[cnte].v = v;
}

void delPlate(int x, int yl, int yr, int v) {
    event[++cnte].op = 2;
    event[cnte].x = x;
    event[cnte].yl = yl;
    event[cnte].yr = yr;
    event[cnte].v = v;
}

void addFruit(int x, int y, int k, int i) {
    event[++cnte].op = 3;
    event[cnte].x = x;
    event[cnte].y = y;
    event[cnte].k = k;
    event[cnte].i = i;
}

void compute(int el, int er, int vl, int vr) {
    if (el > er) {
        return;
    }
    if (vl == vr) {
        for (int i = el; i <= er; i++) {
            int id = eid[i];
            if (event[id].op == 3) {
                ans[event[id].i] = vl;
            }
        }
    } else {
        int mid = (vl + vr) >> 1;
        int lsiz = 0, rsiz = 0;
        for (int i = el; i <= er; i++) {
            int id = eid[i];
            if (event[id].op == 1) {
                if (event[id].v <= mid) {
                    add(event[id].yl, event[id].yr, 1);
                    lset[++lsiz] = id;
                } else {
                    rset[++rsiz] = id;
                }
            } else if (event[id].op == 2) {
                if (event[id].v <= mid) {
                    add(event[id].yl, event[id].yr, -1);
                    lset[++lsiz] = id;
                } else {
                    rset[++rsiz] = id;
                }
            } else {
                int satisfy = query(event[id].y);
                if (satisfy >= event[id].k) {
                    lset[++lsiz] = id;
                } else {
                    event[id].k -= satisfy;
                    rset[++rsiz] = id;
                }
            }
        }
        // 这里为什么不用做撤销？
		// 因为任何一个盘子，一定有两条扫描线
		// 一条扫描线会增加yl..yr的计数
		// 一条扫描线会减少yl..yr的计数
		// 同一个盘子的两条扫描线，一定会在一起，是不可能分开的
		// 所以此时树状数组就是清空的，不需要再做撤销操作
        for (int i = 1; i <= lsiz; i++) {
            eid[el + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsiz; i++) {
            eid[el + lsiz + i - 1] = rset[i];
        }
        compute(el, el + lsiz - 1, vl, mid);
        compute(el + lsiz, er, mid + 1, vr);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p >> q;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    for (int i = 1, a, b, c; i <= p; i++) {
        cin >> a >> b >> c;
        if (ldfn[a] > ldfn[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        int ablca = lca(a, b);
        if (ablca == a || ablca == b) {
            // 类型1，a和b的lca是a或b，2个区域，4个事件产生
			// 类型2，a和b的lca不是a或b，1个区域，2个事件产生
            int son = lcaSon(a, b);
            // (1 ~ dfn[son]-1) (b子树上的dfn范围)
            addPlate(1, ldfn[b], rdfn[b], c);
            delPlate(ldfn[son], ldfn[b], rdfn[b], c);
            // (b子树上的dfn范围) (son子树上最大的dfn序号+1 ~ n)
            addPlate(ldfn[b], rdfn[son] + 1, n, c);
            delPlate(rdfn[b] + 1, rdfn[son] + 1, n, c);
        } else {
            // (a子树上的dfn范围) (b子树上的dfn范围)
            addPlate(ldfn[a], ldfn[b], rdfn[b], c);
            delPlate(rdfn[a] + 1, ldfn[b], rdfn[b], c);
        }
    }
    for (int i = 1, u, v, k; i <= q; i++) {
        cin >> u >> v >> k;
        addFruit(min(ldfn[u], ldfn[v]), max(ldfn[u], ldfn[v]), k, i);
    }
    // 根据x排序，如果x一样，加盘子排最前、删盘子其次、水果最后
    sort(event + 1, event + cnte + 1, EventCmp);
    for (int i = 1; i <= cnte; i++) {
        eid[i] = i;
    }
    compute(1, cnte, 0, INF);
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}