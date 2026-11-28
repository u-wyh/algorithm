// https://www.luogu.com.cn/problem/P4774
// 题意：多组数据，按序打 n 条血量 a_i、回血 p_i 的龙；
// 每次选攻击 <= a_i 的最大剑（无则选最小）砍固定 x 次，
// 之后龙每次回 p_i 直到非负，需血量恰好为 0 击杀并换奖励剑
// 求最小 x（无解输出 -1）。
// 数据范围：T <= 5，1 <= n, m <= 10^5，
// 1 <= a_i <= 10^12，所有 p_i 的最小公倍数 <= 10^12
// 所有武器攻击力 <= 10^6。
// 难度评分：2200（洛谷分级换算）
// 算法标签：扩展中国剩余定理、扩展欧几里得、贪心
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 100001;

long long hp[MAXN];
long long recovery[MAXN];
long long reward[MAXN];
long long attack[MAXN];
long long init[MAXN];

long long d, x, y;

void exgcd(long long a, long long b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        long long temp = x;
        x = y;
        y = temp - y * (a / b);
    }
}

long long multiply(long long a, long long b, long long mod) {
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;
    long long res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

long long allocate(int n, int m) {
    multiset<long long> swords;
    for (int i = 1; i <= m; ++i) {
        swords.insert(init[i]);
    }
    long long max_cnt = 0;
    for (int i = 1; i <= n; ++i) {
        auto it = swords.upper_bound(hp[i]);
        if (it != swords.begin()) {
            --it;
            attack[i] = *it;
            swords.erase(it);
        } else {
            attack[i] = *swords.begin();
            swords.erase(swords.begin());
        }
        swords.insert(reward[i]);
        max_cnt = max(max_cnt, (hp[i] + attack[i] - 1) / attack[i]);
        if (recovery[i] > 0) {
            hp[i] %= recovery[i];
        }
    }
    return max_cnt;
}

long long compute(int n, int m) {
    long long max_att = allocate(n, m);
    long long tail = 0, lcm = 1;
    for (int i = 1; i <= n; ++i) {
        if (recovery[i] == 0) {
            if (attack[i] * max_att != hp[i]) {
                return -1;
            }
            continue;
        }
        long long a = multiply(attack[i], lcm, recovery[i]);
        long long b = recovery[i];
        long long c = (hp[i] - attack[i] * tail) % b;
        c = (c + b) % b;
        exgcd(a, b);
        if (c % d != 0) {
            return -1;
        }
        long long x0 = multiply(x, c / d, b / d);
        long long mod = b / d;
        x0 = (x0 % mod + mod) % mod;
        long long new_lcm = lcm / __gcd(lcm, b / d) * (b / d);
        tail = (tail + multiply(x0, lcm, new_lcm)) % new_lcm;
        lcm = new_lcm;
    }
    if (tail >= max_att) {
        return tail;
    } else {
        long long k = (max_att - tail + lcm - 1) / lcm;
        return k * lcm + tail;
    }
}

signed main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%lld", &hp[i]);
        for (int i = 1; i <= n; ++i) scanf("%lld", &recovery[i]);
        for (int i = 1; i <= n; ++i) scanf("%lld", &reward[i]);
        for (int i = 1; i <= m; ++i) scanf("%lld", &init[i]);
        long long ans = compute(n, m);
        printf("%lld\n", ans);
    }
    return 0;
}