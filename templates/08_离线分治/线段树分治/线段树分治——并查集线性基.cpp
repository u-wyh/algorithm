// 异或最短路，C++版
// 一共有n个节点，m条边，每条边有边权
// 接下来有q条操作，每种操作是如下三种类型中的一种
// 操作 1 x y d : 原图中加入，点x到点y，权值为d的边
// 操作 2 x y   : 原图中删除，点x到点y的边
// 操作 3 x y   : 点x到点y，所有路随便走，沿途边权都异或起来，打印能取得的异或最小值
// 保证x < y，并且任意操作后，图连通、无重边、无自环，所有操作均合法
// 1 <= n、m、q <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF938G
// 测试链接 : https://codeforces.com/problemset/problem/938/G
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题结合了线性基、带权并查集、可撤销并查集等
//x到y可以经过重复的边和点  求边权异或最大值：先找到一条简单路径，求出边权  然后找到所有的环，并求出异或值   进行线性基求最大值
//两点之间的边是可以删除之后再加回来的
//我们设置0这个时间点  因为如果不这样 初始存在的边可能排序后先删除边然后才加边
//注意：这个带权并查集不能扁平化  因为有可撤销操作
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXT = 5000001;
const int BIT = 29;

int n, m, q;

// 端点x、端点y、时间点t、边权w
struct Event {
   int x, y, t, w;
};

//各个事件的排序函数
bool EventCmp(Event a, Event b) {
    if (a.x != b.x) {
        return a.x < b.x;
    } else if (a.y != b.y) {
        return a.y < b.y;
    } else {
        return a.t < b.t;
    }
}

Event event[MAXN << 1];
int eventCnt = 0;

// 操作记录下来
int op[MAXN];
int x[MAXN];
int y[MAXN];
int d[MAXN];

// 可撤销线性基
int basis[BIT + 1];
int inspos[BIT + 1];//记录插入数据的位置
int basiz = 0;

// 带权并查集 + 可撤销并查集
int father[MAXN];
int siz[MAXN];
int eor[MAXN];//每一个节点到自己的代表结点的路径上的权值异或和
int rollback[MAXN][2];
int opsize = 0;

// 时间轴线段树上的区间任务列表
int head[MAXN << 2];
int nxt[MAXT];
int tox[MAXT];
int toy[MAXT];
int tow[MAXT];
int cnt = 0;

int ans[MAXN];

// num插入线性基
void insert(int num) {
    for (int i = BIT; i >= 0; --i) {
        if (num >> i == 1) {
            if (basis[i] == 0) {
                //如果这个位置以前已经存在一个数字了  那么这个数位上的数字不要变
                basis[i] = num;
                inspos[basiz++] = i;//记录插入的位置  方便撤销
                return;
            }
            num ^= basis[i];
        }
    }
}

// num结合线性基，能得到的最小异或值返回
int minEor(int num) {
    for (int i = BIT; i >= 0; --i) {
        num = min(num, num ^ basis[i]);
    }
    return num;
}

// 线性基的撤销，让空间大小回到之前的规模   因为每次加入操作都是在最后面进行加入
void cancel(int oldsiz) {
    while (basiz > oldsiz) {
        basis[inspos[--basiz]] = 0;
    }
}

// 可撤销并查集找集合代表点
int find(int i) {
    while (i != father[i]) {
        i = father[i];
    }
    return i;
}

// 返回i到集合代表点的异或和
int getEor(int i) {
    int res = 0;
    while (i != father[i]) {
        res ^= eor[i];
        i = father[i];
    }
    return res;
}

// 可撤销并查集的合并，增加a和b之间，权值为w的边
// 集合合并的过程中，还要更新eor数组
// 更新eor的方式，参考讲解156，带权并查集
bool Union(int u, int v, int w) {
    int fu = find(u);
    int fv = find(v);
    w = getEor(u) ^ getEor(v) ^ w;//从u到v的一条简单路径的边权
    if (fu == fv) {
        //说明产生了一个环  将这个环的权值加入线性基中
        insert(w);
        return false;
    }
    if (siz[fu] < siz[fv]) {
        int tmp = fu;
        fu = fv;
        fv = tmp;
    }
    father[fv] = fu;
    siz[fu] += siz[fv];
    eor[fv] = w;
    rollback[++opsize][0] = fu;
    rollback[opsize][1] = fv;
    return true;
}

// 并查集的撤销操作
void undo() {
    int fu = rollback[opsize][0];
    int fv = rollback[opsize--][1];
    father[fv] = fv;
    eor[fv] = 0;
    siz[fu] -= siz[fv];
}

// 给某个线段树区间增加任务，点x到点y之间，增加权值为w的边
void addEdge(int idx, int u, int v, int w) {
    nxt[++cnt] = head[idx];
    tox[cnt] = u;
    toy[cnt] = v;
    tow[cnt] = w;
    head[idx] = cnt;
}

void add(int jobl, int jobr, int jobx, int joby, int jobw, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addEdge(i, jobx, joby, jobw);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, jobx, joby, jobw, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobx, joby, jobw, mid + 1, r, i << 1 | 1);
        }
    }
}

void dfs(int l, int r, int i) {
    //这里没有像之前那样拷贝 而是记录在加入之前线性基中的个数  每次向上返回的时候  恢复到这个个数就好
    //因为这样操作比较方便
    int oldsiz = basiz;
    int unionCnt = 0;
    for (int e = head[i]; e; e = nxt[e]) {
        if (Union(tox[e], toy[e], tow[e])) {
            //只有真正的合并了  才需要撤销
            unionCnt++;
        }
    }
    if (l == r) {
        if (op[l] == 3) {
            ans[l] = minEor(getEor(x[l]) ^ getEor(y[l]));//求出最小线性基
        }
    } else {
        int mid = (l + r) >> 1;
        dfs(l, mid, i << 1);
        dfs(mid + 1, r, i << 1 | 1);
    }
    //完全恢复之前的状态
    cancel(oldsiz);
    for (int k = 1; k <= unionCnt; k++) {
        undo();
    }
}

void prepare() {
    //并查集初始化
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        siz[i] = 1;
    }
    sort(event + 1, event + eventCnt + 1, EventCmp);
    int x, y, start, end, d;
    for (int l = 1, r = 1; l <= eventCnt; l = ++r) {
        x = event[l].x;
        y = event[l].y;
        while (r + 1 <= eventCnt && event[r + 1].x == x && event[r + 1].y == y) {
            r++;
        }
        //l到r  全都是关于xy之间的边
        for (int i = l; i <= r; i += 2) {
            start = event[i].t;
            end = (i + 1 <= r) ? (event[i + 1].t - 1) : q;
            d = event[i].w;
            add(start, end, x, y, d, 0, q, 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> event[i].x >> event[i].y >> event[i].w;
        event[i].t = 0;//初始时就存在的边时间设置为0
    }
    eventCnt = m;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> op[i] >> x[i] >> y[i];
        if (op[i] == 1) {
            cin >> d[i];
        }
        if (op[i] != 3) {
            event[++eventCnt].x = x[i];
            event[eventCnt].y = y[i];
            event[eventCnt].t = i;
            event[eventCnt].w = d[i];//删除边 就是将边权设置为0
        }
    }
    prepare();
    dfs(0, q, 1);
    for (int i = 1; i <= q; i++) {
        if (op[i] == 3) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}