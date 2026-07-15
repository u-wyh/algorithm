#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 10200000;
const int mod = 998244353;
ll fact[MAXN + 10], inv_fact[MAXN + 10];

// 快速幂函数，计算a的b次方模mod
ll pow_mod(ll a, ll b) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 预处理阶乘和阶乘的逆元
void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    inv_fact[MAXN] = pow_mod(fact[MAXN], mod - 2);
    for (int i = MAXN - 1; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
    }
}

int main() {
    precompute();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, l, r;
        scanf("%d%d%d%d", &n, &m, &l, &r);
        vector<int> x(n);
        map<int, int> cnt;
        for (int i = 0; i < n; i++) {
            scanf("%d", &x[i]);
            cnt[x[i]]++;
        }
        vector<int> a;
        ll F_out = 1;
        int range_len = r - l + 1;
        // 统计不在[l, r]范围内的数字的出现次数的阶乘乘积
        for (auto &p : cnt) {
            if (p.first < l || p.first > r) {
                F_out = F_out * fact[p.second] % mod;
            } else {
                a.push_back(p.second);
            }
        }
        int k = range_len - a.size(); // 未出现的数字个数
        sort(a.begin(), a.end()); // 对出现次数排序
        int sz = a.size();
        vector<ll> pre(sz + 1, 0);
        for (int i = 0; i < sz; i++) {
            pre[i + 1] = pre[i] + a[i]; // 前缀和
        }
        ll total_a = pre[sz];
        ll low = 0, high = n + m;
        ll T_val = 0;
        // 二分查找最大的T，使得将所有数字的出现次数至少提升到T所需的添加次数不超过m
        while (low <= high) {
            ll mid = (low + high) / 2;
            ll need = 0;
            if (sz == 0) {
                need = mid * k;
            } else if (mid > a[sz - 1]) {
                need = mid * range_len - total_a;
            } else {
                int idx = lower_bound(a.begin(), a.end(), mid) - a.begin();
                need = mid * idx - pre[idx] + mid * k;
            }
            if (need <= m) {
                T_val = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        ll need_val;
        // 计算达到T_val所需的添加次数
        if (sz == 0) {
            need_val = T_val * k;
        } else if (T_val > a[sz - 1]) {
            need_val = T_val * range_len - total_a;
        } else {
            int idx = lower_bound(a.begin(), a.end(), T_val) - a.begin();
            need_val = T_val * idx - pre[idx] + T_val * k;
        }
        ll rem = m - need_val; // 剩余添加次数

        int idx2;
        if (sz == 0) {
            idx2 = 0;
        } else {
            idx2 = upper_bound(a.begin(), a.end(), T_val) - a.begin();
        }
        ll count = idx2 + k; // 需要均匀分配的数字个数
        ll base = rem / count; // 每个数字基础分配次数
        ll rem2 = rem % count; // 剩余分配次数

        ll P = F_out;
        // 处理出现次数大于T_val的数字
        for (int i = idx2; i < sz; i++) {
            P = P * fact[a[i]] % mod;
        }
        // 处理均匀分配后的数字出现次数阶乘乘积
        P = P * pow_mod(fact[T_val + base], count - rem2) % mod;
        P = P * pow_mod(fact[T_val + base + 1], rem2) % mod;

        // 计算答案：期望轮数 = (n+m)! / P
        ll ans = fact[n + m] * pow_mod(P, mod - 2) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}