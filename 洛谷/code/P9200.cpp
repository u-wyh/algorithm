#include <iostream>
#include <vector>
#include <climits>
using namespace std;

typedef long long ll;
const ll Max = 25000000000LL; // 定义值域范围 [-25e9, 25e9]

// 动态开点线段树的节点结构
struct Node {
    int lson, rson; // 左右子节点指针
    ll sz;          // 当前区间内点的数量
    ll sum;         // 当前区间内所有点的坐标之和
};

Node tree[12500000]; // 预先分配线段树节点空间
int tot = 0;         // 节点计数器
int root = 0;        // 根节点指针

// 更新节点信息（从子节点汇总）
void update(int p) {
    tree[p].sz = tree[p].sum = 0;
    if (tree[p].lson) {
        tree[p].sz += tree[tree[p].lson].sz;
        tree[p].sum += tree[tree[p].lson].sum;
    }
    if (tree[p].rson) {
        tree[p].sz += tree[tree[p].rson].sz;
        tree[p].sum += tree[tree[p].rson].sum;
    }
}

// 在线段树中修改某个位置的值
void modify(int &p, ll l, ll r, ll pos, ll val) {
    if (!p) p = ++tot; // 动态创建节点
    if (l == r) {
        tree[p].sz += val;
        tree[p].sum += val * pos;
        return;
    }
    ll mid = (l + r) >> 1;
    if (pos <= mid) modify(tree[p].lson, l, mid, pos, val);
    else modify(tree[p].rson, mid+1, r, pos, val);
    update(p); // 更新当前节点信息
}

// 查询区间 [ql, qr] 内的点数和坐标和
pair<ll, ll> query(int p, ll l, ll r, ll ql, ll qr) {
    if (!p) return {0, 0}; // 空节点返回零
    if (ql <= l && r <= qr) {
        return {tree[p].sz, tree[p].sum}; // 完全包含，直接返回
    }
    ll mid = (l + r) >> 1;
    pair<ll, ll> res = {0, 0};
    if (ql <= mid) {
        auto left_res = query(tree[p].lson, l, mid, ql, qr);
        res.first += left_res.first;
        res.second += left_res.second;
    }
    if (qr > mid) {
        auto right_res = query(tree[p].rson, mid+1, r, ql, qr);
        res.first += right_res.first;
        res.second += right_res.second;
    }
    return res;
}

// 查找第k小的点
ll find_kth(int p, ll l, ll r, ll k) {
    if (l == r) return l;
    ll mid = (l + r) >> 1;
    ll left_sz = tree[tree[p].lson].sz; // 左子树的大小
    if (left_sz >= k) {
        return find_kth(tree[p].lson, l, mid, k);
    } else {
        return find_kth(tree[p].rson, mid+1, r, k - left_sz);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    vector<ll> c(n+2); // 存储c_i系数
    vector<ll> e(n+1); // 存储e_i电荷量
    ll sum_e = 0;
    
    // 读入c数组
    for (int i = 1; i <= n+1; i++) {
        scanf("%lld", &c[i]);
    }
    
    // 读入e数组并计算总和
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &e[i]);
        sum_e += e[i];
    }
    
    // 计算第n+1个实验腔的电荷量（根据电荷守恒定律）
    ll e0 = -sum_e;

    // 重新组织E和C数组，长度为n+1
    vector<ll> E(n+1);
    vector<ll> C(n+1);
    for (int i = 0; i < n; i++) {
        E[i] = e[i+1];      // E[0..n-1] = e[1..n]
        C[i] = c[i+1];      // C[0..n-1] = c[1..n]
    }
    E[n] = e0;              // E[n] = e0
    C[n] = c[n+1];          // C[n] = c[n+1]

    // 计算前缀和数组S，S[i]表示从起点到i的电荷量代数和
    vector<ll> S(n+1);
    S[0] = 0;
    for (int i = 1; i <= n; i++) {
        S[i] = S[i-1] + E[i-1];
    }

    // 构建权重数组W，W[i]表示在位置S[i]处的权重（即c_i）
    vector<ll> W(n+1, 0);
    for (int i = 0; i < n; i++) {
        W[i+1] += C[i]; // 对应原实验腔的权重
    }
    W[0] += C[n];       // 第n+1个实验腔的权重放在S[0]处

    // 初始化线段树，将所有点插入
    ll total_weight = 0;
    for (int i = 0; i <= n; i++) {
        total_weight += W[i];
        modify(root, -Max, Max, S[i], W[i]);
    }

    // 计算初始能量：找到加权中位数点，计算所有点到该点的加权距离和
    ll kth = (total_weight + 1) / 2; // 中位数的位置
    ll mid_val = find_kth(root, -Max, Max, kth); // 找到中位数点的值
    auto right = query(root, -Max, Max, mid_val+1, Max); // 大于中位数的点
    auto left = query(root, -Max, Max, -Max, mid_val-1); // 小于中位数的点
    ll energy = (right.second - mid_val * right.first) + (mid_val * left.first - left.second);
    ll ans = energy; // 初始答案

    // 枚举所有可能的插入位置（从n到1）
    for (int i = n; i >= 1; i--) {
        // 从线段树中移除当前位置和下一个位置的点
        if (i == n) {
            modify(root, -Max, Max, S[n], -W[n]);
            modify(root, -Max, Max, S[0], -W[0]);
        } else {
            modify(root, -Max, Max, S[i], -W[i]);
            modify(root, -Max, Max, S[i+1], -W[i+1]);
        }

        // 交换相邻的E和C值（模拟插入位置的改变）
        swap(E[i-1], E[i]);
        swap(C[i-1], C[i]);

        // 更新权重数组W
        if (i == n) {
            W[n] = C[n-1];
            W[0] = C[n];
        } else {
            W[i] = C[i-1];
            W[i+1] = C[i];
        }

        // 更新前缀和数组S
        S[i] = S[i-1] + E[i-1];
        if (i < n) {
            S[i+1] = S[i] + E[i];
        }

        // 将更新后的点重新插入线段树
        if (i == n) {
            modify(root, -Max, Max, S[n], W[n]);
            modify(root, -Max, Max, S[0], W[0]);
        } else {
            modify(root, -Max, Max, S[i], W[i]);
            modify(root, -Max, Max, S[i+1], W[i+1]);
        }

        // 重新计算能量
        mid_val = find_kth(root, -Max, Max, kth);
        right = query(root, -Max, Max, mid_val+1, Max);
        left = query(root, -Max, Max, -Max, mid_val-1);
        energy = (right.second - mid_val * right.first) + (mid_val * left.first - left.second);
        
        // 更新最小能量
        if (energy < ans) ans = energy;
    }

    printf("%lld\n", ans);
    return 0;
}