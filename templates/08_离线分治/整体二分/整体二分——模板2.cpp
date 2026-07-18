// 区间内第k小，第二种写法，C++版
// 给定一个长度为n的数组，接下来有m条查询，格式如下
// 查询 l r k : 打印[l..r]范围内第k小的值
// 1 <= n、m <= 2 * 10^5
// 1 <= 数组中的数字 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P3834
// 本题是讲解157，可持久化线段树模版题，现在作为整体二分的模版题
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这种做法是设置好一个used  即从1~used都已经生效了  
//如果当前需要生效的范围超过used  那么used就会增加至需要的地方
//否则就会减少到需要的范围
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;

// 位置i，数值v
struct Number {
    int i, v;
};

bool NumberCmp(Number x, Number y) {
    return x.v < y.v;
}

int n, m;

Number arr[MAXN];

// 查询
//qid可能会发生变化 但是l r k则会保持不变
int qid[MAXN];
int l[MAXN];
int r[MAXN];
int k[MAXN];

// 树状数组
int tree[MAXN];
int used = 0;//表示从1到used都是有效的

int lset[MAXN];
int rset[MAXN];

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

//第二种写法
//和第一种方法的区别就是他不要更改k  而是通过used判断当前在树状数组中的是不是满足要求
//这个时间复杂度也不会很大  因为每次都是将任务先执行左儿子的  used变化不会很大
void compute(int ql, int qr, int vl, int vr) {
    if (ql > qr) {
        return;
    }
    if (vl == vr) {
        for (int i = ql; i <= qr; i++) {
            ans[qid[i]] = arr[vl].v;
        }
    } else {
        int mid = (vl + vr) / 2;
        while (used < mid) {
            used++;
            add(arr[used].i, 1);
        }
        while (used > mid) {
            add(arr[used].i, -1);
            used--;
        }
        int lsiz = 0, rsiz = 0;
        for (int i = ql; i <= qr; i++) {
            int id = qid[i];
            int satisfy = query(l[id], r[id]);
            if (satisfy >= k[id]) {
                lset[++lsiz] = id;
            } else {
                rset[++rsiz] = id;
            }
        }
        for (int i = 1; i <= lsiz; i++) {
            qid[ql + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsiz; i++) {
            qid[ql + lsiz + i - 1] = rset[i];
        }
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