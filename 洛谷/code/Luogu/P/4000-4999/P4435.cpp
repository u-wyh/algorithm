#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int n, q;
int val[MAXN];

// 线段树节点结构体
struct Node {
    long long tree; // 区间内有趣子数组的数量
    int gcdval;     // 区间的GCD值
    vector<pair<int, int>> pre; // 前缀GCD列表 (GCD值, 连续长度)
    vector<pair<int, int>> suf; // 后缀GCD列表 (GCD值, 连续长度)
    
    // 构造函数
    Node() : tree(0), gcdval(0) {}
    Node(int value) {
        gcdval = value;
        tree = (value > 1) ? 1 : 0;
        pre.push_back({value, 1});
        suf.push_back({value, 1});
    }
};

Node tree[MAXN << 2]; // 线段树数组

// 快速读入函数
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

// 计算最大公约数
inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 合并两个线段树节点，返回合并后的节点
Node merge(const Node &left, const Node &right) {
    Node result;
    
    // 计算整个区间的GCD
    result.gcdval = gcd(left.gcdval, right.gcdval);
    
    // 计算跨越中点的有趣子数组数量
    long long tmp = 0;
    int len = 0;
    
    // 计算右子树前缀列表的总长度
    for (int i = 0; i < (int)right.pre.size(); i++) {
        len += right.pre[i].second;
    }
    
    // 遍历左子树后缀列表和右子树前缀列表
    for (int i = 0, j = (int)right.pre.size() - 1; i < (int)left.suf.size(); i++) {
        while (j != -1 && gcd(left.suf[i].first, right.pre[j].first) == 1) {
            len -= right.pre[j].second;
            j--;
        }
        tmp += (long long)left.suf[i].second * len;
    }
    
    result.tree = left.tree + right.tree + tmp;
    
    // 合并前缀GCD列表
    result.pre = left.pre;
    for (int i = 0; i < (int)right.pre.size(); i++) {
        int g = gcd(left.gcdval, right.pre[i].first);
        if (g == left.gcdval) {
            result.pre.back().second += right.pre[i].second;
        } else {
            result.pre.push_back({g, right.pre[i].second});
        }
    }
    
    // 合并后缀GCD列表
    result.suf = right.suf;
    for (int i = 0; i < (int)left.suf.size(); i++) {
        int g = gcd(right.gcdval, left.suf[i].first);
        if (g == right.gcdval) {
            result.suf.back().second += left.suf[i].second;
        } else {
            result.suf.push_back({g, left.suf[i].second});
        }
    }
    
    return result;
}

// 构建线段树
void build(int l, int r, int idx) {
    if (l == r) {
        tree[idx] = Node(val[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, idx << 1);
    build(mid + 1, r, idx << 1 | 1);
    tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
}

// 更新线段树
void update(int pos, int new_val, int l, int r, int idx) {
    if (l == r) {
        tree[idx] = Node(new_val);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        update(pos, new_val, l, mid, idx << 1);
    } else {
        update(pos, new_val, mid + 1, r, idx << 1 | 1);
    }
    tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
}

// 查询线段树
Node query(int ql, int qr, int l, int r, int idx) {
    if (ql <= l && r <= qr) {
        return tree[idx];
    }
    int mid = (l + r) >> 1;
    if (qr <= mid) {
        return query(ql, qr, l, mid, idx << 1);
    } else if (ql > mid) {
        return query(ql, qr, mid + 1, r, idx << 1 | 1);
    } else {
        Node left = query(ql, mid, l, mid, idx << 1);
        Node right = query(mid + 1, qr, mid + 1, r, idx << 1 | 1);
        return merge(left, right);
    }
}

int main() {
    n = read(), q = read();
    for (int i = 1; i <= n; i++) {
        val[i] = read();
    }
    
    build(1, n, 1);
    
    for (int i = 0; i < q; i++) {
        int op = read(), l = read(), r = read();
        if (op == 1) {
            update(l, r, 1, n, 1);
        } else {
            Node result = query(l, r, 1, n, 1);
            printf("%lld\n", result.tree);
        }
    }
    
    return 0;
}