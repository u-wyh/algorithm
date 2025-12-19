#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int maxn = 500005;
int n;
char c[maxn];

// 线段树节点结构体
struct Node {
    int pre;  // 最大前缀和
    int suf;  // 最大后缀和
    int mx;   // 最大子段和
    int sum;  // 区间和
};

Node t[maxn << 2];  // 线段树数组

// 合并左右子节点信息到父节点
void push_up(int x) {
    int ls = x << 1, rs = x << 1 | 1;  // 左右子节点索引
    t[x].sum = t[ls].sum + t[rs].sum;  // 区间和等于左右子节点区间和之和
    t[x].pre = max(t[ls].pre, t[ls].sum + t[rs].pre);  // 最大前缀和
    t[x].suf = max(t[rs].suf, t[rs].sum + t[ls].suf);  // 最大后缀和
    t[x].mx = max({t[ls].mx, t[rs].mx, t[ls].suf + t[rs].pre});  // 最大子段和
}

// 构建线段树
void build(int x, int l, int r) {
    if (l == r) {
        int val = (c[l] == 'C') ? 1 : -1;  // 字符转换为数值
        t[x].sum = val;  // 区间和
        t[x].pre = val;  // 最大前缀和
        t[x].suf = val;  // 最大后缀和
        t[x].mx = val;   // 最大子段和
        if (val < 0) {
            // 如果值为负，则最大前缀和、后缀和和子段和至少为0（即不选该字符）
            t[x].pre = 0;
            t[x].suf = 0;
            t[x].mx = 0;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);  // 构建左子树
    build(x << 1 | 1, mid + 1, r);  // 构建右子树
    push_up(x);  // 合并左右子节点信息
}

// 查询线段树
Node query(int x, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return t[x];  // 当前节点区间完全包含在查询区间内
    }
    int mid = (l + r) >> 1;
    if (R <= mid) {
        return query(x << 1, l, mid, L, R);  // 查询左子树
    } else if (L > mid) {
        return query(x << 1 | 1, mid + 1, r, L, R);  // 查询右子树
    } else {
        // 查询区间跨越左右子树
        Node left_node = query(x << 1, l, mid, L, R);
        Node right_node = query(x << 1 | 1, mid + 1, r, L, R);
        Node res;
        res.sum = left_node.sum + right_node.sum;  // 合并区间和
        res.pre = max(left_node.pre, left_node.sum + right_node.pre);  // 合并最大前缀和
        res.suf = max(right_node.suf, right_node.sum + left_node.suf);  // 合并最大后缀和
        res.mx = max({left_node.mx, right_node.mx, left_node.suf + right_node.pre});  // 合并最大子段和
        return res;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    cin >> (c + 1);  // 读取字符串，从索引1开始
    build(1, 1, n);  // 构建线段树
    int q;
    cin >> q;
    while (q--) {
        int L, R;
        cin >> L >> R;
        Node res = query(1, 1, n, L, R);  // 查询区间[L, R]的信息
        cout << res.mx - res.sum << '\n';  // 输出需要删除的字符数
    }
    return 0;
}