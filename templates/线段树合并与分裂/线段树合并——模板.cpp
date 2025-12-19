// 晋升者计数，C++版
// 一共有n个人，给定每个人的能力值arr[i]，所有人组成一棵树，代表公司的组织
// 1号人是整个公司的老板，从2号人开始，给定每个人的上司编号fa[i]
// 打印第i号人为头的子树中，有多少个人的能力值 > 第i号人的能力值，一共n条打印
// 1 <= n <= 10^5
// 1 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P3605
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题的时间复杂度和空间复杂度都是 O(n*logn)级别的
// 首先每个节点建立一个自己的开点线段树  n个节点每个节点高度是logn  
// 在线段树合并的过程中实际上是不会在添加节点的了  全部复用以前的节点
// 在合并的过程中，每个节点只会被使用一次  合并之后  他就被融入到父亲中了  就不会被使用了
// 那么时间复杂度就是空间复杂度
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXT = MAXN * 40;

int n;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg;

int arr[MAXN];
int sorted[MAXN];
int cntv;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int siz[MAXT];
int cntt;

int ans[MAXN];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

int kth(int num) {
    int left = 1, right = cntv, ret = 0;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (sorted[mid] <= num) {
            ret = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ret;
}

void up(int i) {
    siz[i] = siz[ls[i]] + siz[rs[i]];
}

int add(int jobi, int l, int r, int i) {
    int rt = i;
    if (rt == 0) {
        rt = ++cntt;
    }
    if (l == r) {
        siz[rt]++;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            ls[rt] = add(jobi, l, mid, ls[rt]);
        } else {
            rs[rt] = add(jobi, mid + 1, r, rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l, int r, int t1, int t2) {
    if (t1 == 0 || t2 == 0) {
        return t1 + t2;
    }
    if (l == r) {
        // 遇到叶子结点
        siz[t1] += siz[t2];
    } else {
        int mid = (l + r) >> 1;
        ls[t1] = merge(l, mid, ls[t1], ls[t2]);
        rs[t1] = merge(mid + 1, r, rs[t1], rs[t2]);
        up(t1);
    }
    return t1;
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl > jobr || i == 0) {
        // 这个地方要注意 i==0的情况
        return 0;
    }
    if (jobl <= l && r <= jobr) {
        return siz[i];
    }
    int mid = (l + r) >> 1;
    int ret = 0;
    if (jobl <= mid) {
        ret += query(jobl, jobr, l, mid, ls[i]);
    }
    if (jobr > mid) {
        ret += query(jobl, jobr, mid + 1, r, rs[i]);
    }
    return ret;
}

void calc(int u, int fa) {
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v != fa) {
            calc(v, u);
            // 合并线段树  将儿子的合并到父亲节点上
            root[u] = merge(1, cntv, root[u], root[v]);
        }
    }
    // 查询子树中大于自己的数量
    ans[u] = query(arr[u] + 1, cntv, 1, cntv, root[u]);
}

void compute() {
    for (int i = 1; i <= n; i++) {
        sorted[i] = arr[i];
    }
    sort(sorted + 1, sorted + n + 1);
    cntv = 1;
    for (int i = 2; i <= n; i++) {
        if (sorted[cntv] != sorted[i]) {
            sorted[++cntv] = sorted[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        arr[i] = kth(arr[i]);
    }
    // 对每个节点建立一个自己的开点线段树
    for (int i = 1; i <= n; i++) {
        root[i] = add(arr[i], 1, cntv, root[i]);
    }
    // 递归计算答案
    calc(1, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 2, fa; i <= n; i++) {
        cin >> fa;
        addEdge(fa, i);
        addEdge(i, fa);
    }
    compute();
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}