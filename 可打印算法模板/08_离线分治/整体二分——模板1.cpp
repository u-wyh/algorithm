// 用途：整体二分求离线区间第 k 小。
// 时间：O((n+q)log V log n)。
// 空间：O(n+q)。
// 例题：https://www.luogu.com.cn/problem/P3834
// 题意：多次查询静态数组区间第 k 小。
// 思路：对答案值域递归二分，树状数组统计左半值域内的数量。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;

int n, m;

// 位置i，数值v
struct Number {
    int i, v;
};

bool NumberCmp(Number x, Number y) {
    return x.v < y.v;
}

Number arr[MAXN];

// 查询
//qid可能会发生变化 但是l r k则会保持不变  这里的不变指的是下标不变  k的值是会发生变化的
int qid[MAXN];
int l[MAXN];
int r[MAXN];
int k[MAXN];

// 树状数组
int tree[MAXN];

// 整体二分
int lset[MAXN];
int rset[MAXN];

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

// 整体二分的第一种写法
// 问题范围[ql..qr]，答案范围[vl..vr]，答案范围的每个下标都是数字的排名
void compute(int ql, int qr, int vl, int vr) {
    if (ql > qr) {
        //表示这个区间没有问题了
        return;
    }
    if (vl == vr) {
        //节点区间是一个节点  那么这个节点就是答案
        for (int i = ql; i <= qr; i++) {
            ans[qid[i]] = arr[vl].v;
        }
    } else {
        int mid = (vl + vr) >> 1;
        for (int i = vl; i <= mid; i++) {
            //将前一半的节点加在树状数组上
            add(arr[i].i, 1);
        }
        int lsiz = 0, rsiz = 0;//分往左边的问题数目  和   右边的问题数目
        for (int i = ql; i <= qr; i++) {
            int id = qid[i];
            int satisfy = query(l[id], r[id]);//查询区间上的数目
            if (satisfy >= k[id]) {
                //表示满足要求  去左边
                lset[++lsiz] = id;
            } else {
                //否则减去贡献  去右边
                k[id] -= satisfy;
                rset[++rsiz] = id;
            }
        }
        //将左右编号重新放回qid数组
        for (int i = 1; i <= lsiz; i++) {
            qid[ql + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsiz; i++) {
            qid[ql + lsiz + i - 1] = rset[i];
        }
        // 撤回数据状况
        for (int i = vl; i <= mid; i++) {
            add(arr[i].i, -1);
        }
        // 左右两侧各自递归
        compute(ql, ql + lsiz - 1, vl, mid);
        compute(ql + lsiz, qr, mid + 1, vr);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        arr[i].i = i;
        cin >> arr[i].v;
    }
    for (int i = 1; i <= m; i++) {
        qid[i] = i;
        cin >> l[i] >> r[i] >> k[i];
    }
    sort(arr + 1, arr + n + 1, NumberCmp);
    compute(1, m, 1, n);
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
