#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXP = 20000000;

int phi[MAXP + 10]; // 存储欧拉函数值
int prime[MAXP / 10 + 10], cnt; // 存储素数和素数计数
bool vis[MAXP + 10]; // 标记是否为素数

// 初始化欧拉函数表
void init_phi() {
    phi[1] = 1;
    for (int i = 2; i <= MAXP; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= MAXP; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

// 快速幂取模函数
LL power_mod(LL base, LL exponent, LL p) {
    base %= p;
    LL res = 1;
    while (exponent) {
        if (exponent & 1) res = res * base % p;
        base = base * base % p;
        exponent >>= 1;
    }
    return res;
}

// 检查base的exponent次方是否超过limit
bool check_overflow(LL base, LL exponent, LL limit) {
    if (base >= limit) return true;
    if (base == 1) return limit <= 1;
    if (exponent > 50) return true;
    LL power = 1;
    for (int i = 0; i < exponent; i++) {
        power = power * base;
        if (power >= limit) return true;
    }
    return false;
}

// 递归计算指数塔模p的值
pair<LL, bool> solve(int l, int r, int p, int limit, const function<LL(int)>& get_val) {
    if (l > r) return {1, false}; // 空区间，返回1且不超过限制
    if (p == 1) return {0, true}; // 模数为1，结果为0且超过限制
    LL a_l = get_val(l); // 获取当前位置的值
    if (l == r) {
        // 单点情况，直接判断是否超过limit
        if (a_l >= limit) return {a_l % p, true};
        else return {a_l % p, false};
    }
    int next_p = phi[p]; // 下一层的模数
    // 递归计算下一层的结果
    auto [exp_val, overflow_exp] = solve(l + 1, r, next_p, phi[next_p], get_val);
    LL real_exp = overflow_exp ? exp_val + next_p : exp_val; // 根据是否超过限制调整指数
    LL result = power_mod(a_l, real_exp, p); // 计算当前层的结果
    bool overall_overflow = check_overflow(a_l, real_exp, limit); // 检查是否超过限制
    return {result, overall_overflow};
}

// 树状数组类
class Fenw {
    int n;
    vector<LL> tree;
public:
    Fenw(int n) : n(n), tree(n + 10, 0) {}
    // 更新树状数组
    void update(int i, LL x) {
        for (; i <= n; i += i & -i) tree[i] += x;
    }
    // 查询树状数组
    LL query(int i) {
        LL s = 0;
        for (; i; i -= i & -i) s += tree[i];
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init_phi(); // 初始化欧拉函数表
    int n, m;
    cin >> n >> m;
    vector<LL> init_a(n + 1);
    Fenw fenw(n); // 初始化树状数组
    for (int i = 1; i <= n; i++) {
        cin >> init_a[i];
    }
    while (m--) {
        int op, l, r;
        LL x;
        cin >> op >> l >> r >> x;
        if (op == 1) {
            // 区间加操作
            fenw.update(l, x);
            fenw.update(r + 1, -x);
        } else {
            int p = x;
            // 获取当前值的函数
            auto get_val = [&](int i) {
                return init_a[i] + fenw.query(i);
            };
            // 计算指数塔模p的结果
            LL ans = solve(l, r, p, phi[p], get_val).first;
            cout << ans << '\n';
        }
    }
    return 0;
}