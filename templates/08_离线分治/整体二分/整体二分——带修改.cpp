// 带修改的区间第k小，C++版
// 给定一个长度为n的数组arr，接下来是m条操作，每种操作是如下两种类型的一种
// 操作 C x y   : 把x位置的值修改成y
// 操作 Q x y v : 查询arr[x..y]范围上第v小的值
// 1 <= n、m <= 10^5
// 1 <= 数组中的值 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P2617
// 本题是讲解160，树套树模版题，现在作为带修改的整体二分模版题
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这种整体二分将修改和查询放在一起同时二分
//这道题很难想到整体二分的这种做法，一般还是用树套树来解决
//这道题是按照操作的数值进行二分
//加操作、减操作分别是一个位置上的数字生效和失效(一个操作一般会对应两个事件：加入和被替代（删除）,当然如果之后没有被替代  那么就是一个事件)
//使用第一种整体二分方法计算
// 这样做的正确性是根据 如果想要新加入一个数据  那么就先把原来位置上的数字删除  然后才会加入一个新的数字
// 操作的时候 保持操作间的相对顺序不变
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

//操作编号对应el~er  vl~vr对应操作的值的限制
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
                if (v[id] <= satisfy) {
                    lset[++lsiz] = id;
                } else {
                    v[id] -= satisfy;//对应第一种修改
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
        //还原操作
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