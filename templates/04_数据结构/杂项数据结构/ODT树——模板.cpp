//https://codeforces.com/problemset/problem/896/C
//1 l r x ：将[l,r]区间所有数加上x
//2 l r x ：将[l,r]区间所有数改成x
//3 l r x ：输出将[l,r] 区间从小到大排序后的第x个数是的多少
//4 l r x y ：输出[l,r] 区间每个数字的x次方的和模y的值
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define IT set<Node>::iterator

// 定义区间节点结构体
struct Node {
    int l, r;       // 区间的左右端点
    mutable int v;  // 区间的值，mutable 允许在 const 对象中修改
    Node(int L, int R = -1, int V = 0) : l(L), r(R), v(V) {}
    // 重载 < 运算符，用于 set 排序
    bool operator<(const Node &o) const {
        return l < o.l;
    }
};

set<Node> s; // 使用 set 存储区间节点

// 将区间在 pos 处分割，返回分割后的右区间迭代器
IT split(int pos) {
    IT it = s.lower_bound(Node(pos)); // 找到第一个左端点 >= pos 的区间
    if (it != s.end() && it->l == pos)
        return it; // 如果 pos 正好是某个区间的起点，直接返回
    --it; // 否则找到包含 pos 的区间
    int L = it->l, R = it->r, V = it->v;
    s.erase(it); // 删除原区间
    s.insert(Node(L, pos - 1, V)); // 插入左半部分
    return s.insert(Node(pos, R, V)).first; // 插入右半部分并返回迭代器
    // 返回一个pair，其中第一个元素是一个迭代器，指向插入的元素（或已经存在的元素），
    // 第二个元素是一个布尔值，表示插入是否成功。
}

// 区间赋值操作
void assign(int l, int r, int val) {
    IT itr = split(r + 1), itl = split(l); // 分割区间 [l, r]
    s.erase(itl, itr); // 删除 [l, r] 内的所有区间 删除从itl到itr之间的所有元素（不包括itr）
    s.insert(Node(l, r, val)); // 插入新的区间
}

// 区间加法操作
void add(int l, int r, int val) {
    IT itr = split(r + 1), itl = split(l); // 分割区间 [l, r]
    for (; itl != itr; ++itl)
        itl->v += val; // 对每个区间内的值加上 val
}

// 查询区间第 k 小的数
int kth(int l, int r, int k) {
    vector<pair<int, int>> v; // 存储区间内的值和长度
    IT itr = split(r + 1), itl = split(l); // 分割区间 [l, r]
    for (; itl != itr; ++itl)
        v.push_back(make_pair(itl->v, itl->r - itl->l + 1)); // 收集区间信息
    sort(v.begin(), v.end()); // 按值排序
    for (auto p : v) {
        k -= p.second; // 减去当前值的个数
        if (k <= 0) return p.first; // 如果 k <= 0，返回当前值
    }
    return -1; // 未找到
}

// 快速幂函数，计算 a^b % mod
int powmod(int a, int b, int mod) {
    int res = 1;
    a %= mod;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

// 计算区间 [l, r] 内每个数的 x 次方的和，模 mod
int sum(int l, int r, int x, int mod) {
    int res = 0;
    IT itr = split(r + 1), itl = split(l); // 分割区间 [l, r]
    for (; itl != itr; ++itl)
        res = (res + (itl->r - itl->l + 1) * powmod(itl->v, x, mod)) % mod; // 累加每个区间的贡献
    return res;
}

signed main() {
    int n, m, seed, vmax;
    cin >> n >> m >> seed >> vmax;

    // 随机数生成器
    auto rnd = [&]() {
        int ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    };

    // 初始化数组
    for (int i = 1; i <= n; ++i) {
        int a = rnd() % vmax + 1; // 生成随机数
        s.insert(Node(i, i, a)); // 插入区间节点
    }

    // 处理 m 个操作
    for (int i = 1; i <= m; ++i) {
        int op = rnd() % 4 + 1; // 随机生成操作类型
        int l = rnd() % n + 1; // 随机生成区间左端点
        int r = rnd() % n + 1; // 随机生成区间右端点
        if (l > r)
            swap(l, r); // 确保 l <= r

        int x, y;
        if (op == 3) {
            x = rnd() % (r - l + 1) + 1; // 随机生成第 k 小的 k
        } else {
            x = rnd() % vmax + 1; // 随机生成 x
        }

        if (op == 4) {
            y = rnd() % vmax + 1; // 随机生成模数 y
        }

        // 根据操作类型调用相应函数
        if (op == 1) {
            add(l, r, x); // 区间加
        } else if (op == 2) {
            assign(l, r, x); // 区间赋值
        } else if (op == 3) {
            cout << kth(l, r, x) << endl; // 区间第 k 小
        } else if (op == 4) {
            cout << sum(l, r, x, y) << endl; // 区间 x 次方和
        }
    }

    return 0;
}
