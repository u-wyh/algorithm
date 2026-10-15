// 用途：整体二分处理单点赋值和区间第 k 小。
// 时间：O((n+q)log V log n)。
// 空间：O(n+q)。
// 例题：https://www.luogu.com.cn/problem/P2617
// 题意：数组支持单点赋值，穿插查询当时区间的第 k 小值。
// 思路：赋值拆成删除旧值、加入新值；按事件原顺序扫描，用树状数组计数并递归二分答案值域。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXE = MAXN << 2;
const int INF = 1000000001;

int n, m;

int arr[MAXN];

// 事件编号组成的数组
int eid[MAXE];
// op == 1，代表修改事件，x处，值y，效果v
// op == 2，代表查询事件，[x..y]范围上查询第v小，q表示问题的编号
int op[MAXE];
int x[MAXE];
int y[MAXE];
int v[MAXE];
int q[MAXE];
int cnte = 0;
int cntq = 0;//辅助填写ans数组

// 树状数组
int tree[MAXN];

// 整体二分
int lset[MAXE];
int rset[MAXE];

// 查询的答案
int ans[MAXN];

int lowbit(int i) {
    return i & -i;
}

void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

int sum(int i) {
    int ret = 0;
    while (i > 0) {
        ret += tree[i];
        i -= lowbit(i);
    }
    return ret;
}

int query(int l, int r) {
    return sum(r) - sum(l - 1);
}

// eid[el..er] 保留事件的时间先后；答案值落在 [vl,vr]。
void compute(int el, int er, int vl, int vr) {
    if (el > er) {
        return;
    }
    if (vl == vr) {
        for (int i = el; i <= er; i++) {
            int id = eid[i];
            if (op[id] == 2) {
                ans[q[id]] = vl;
            }
        }
    } else {
        int mid = (vl + vr) >> 1;
        int lsiz = 0, rsiz = 0;
        // 扫描时只把值 <=mid 的增删事件加入树状数组。
        for (int i = el; i <= er; i++) {
            int id = eid[i];
            //保证操作顺序相对不变  即保证时序性没有被破坏
            if (op[id] == 1) {
                if (y[id] <= mid) {
                    add(x[id], v[id]);
                    lset[++lsiz] = id;
                } else {
                    rset[++rsiz] = id;
                }
            } else {
                int satisfy = query(x[id], y[id]);
                // 左半值域已有至少第 k 个数，答案就在左半。
                if (v[id] <= satisfy) {
                    lset[++lsiz] = id;
                } else {
                    v[id] -= satisfy; // 去掉左半的数量，变成右半的第几小。
                    rset[++rsiz] = id;
                }
            }
        }
        for (int i = 1; i <= lsiz; i++) {
            eid[el + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsiz; i++) {
            eid[el + lsiz + i - 1] = rset[i];
        }
        // 清掉本层加入的事件，两个子问题从空树状数组开始。
        for (int i = 1; i <= lsiz; i++) {
            int id = lset[i];
            if (op[id] == 1 && y[id] <= mid) {
                add(x[id], -v[id]);
            }
        }
        compute(el, el + lsiz - 1, vl, mid);
        compute(el + lsiz, er, mid + 1, vr);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        //一开始加入数据认为是一个添加操作
        cin >> arr[i];
        op[++cnte] = 1;
        x[cnte] = i;
        y[cnte] = arr[i];
        v[cnte] = 1;
    }
    for (int i = 1; i <= m; i++) {
        char type;
        cin >> type;
        if (type == 'C') {
            //修改操作对应一个原先数据的删除和新数据的添加
            int a, b;
            cin >> a >> b;
            op[++cnte] = 1;
            x[cnte] = a;
            y[cnte] = arr[a];
            v[cnte] = -1;

            op[++cnte] = 1;
            x[cnte] = a;
            y[cnte] = b;
            v[cnte] = 1;
            arr[a] = b;
        } else {
            op[++cnte] = 2;
            cin >> x[cnte] >> y[cnte] >> v[cnte];
            q[cnte] = ++cntq;
        }
    }
    for (int i = 1; i <= cnte; i++) {
        eid[i] = i;
    }
    compute(1, cnte, 0, INF);
    for (int i = 1; i <= cntq; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
