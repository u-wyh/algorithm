// https://www.luogu.com.cn/problem/P9889
// 题意：多组数据（共 T 组）。
// 直线上房屋东边 1..n 米处有 n 株植物，初始防御值 d_i = 0，
// 生长速度 a_i。
// 机器人从房屋（坐标 0）出发，
// 至多移动 m 步（每步向东或向西走 1 米，可走到 <= 0 或 > n 处），
// 到达某植物位置时为其加 a_i 防御值。
// 求最大化 min_{1 <= i <= n} d_i。
// 题意：第一行输入 T，每组输入 n, m 及 a_1..a_n；
// 每组输出一行一个整数。
// 数据范围：2 <= n <= 10^5，0 <= m <= 10^12，
// 1 <= a_i <= 10^5
// sum(n) <= 10^6（未显式给出 T 上界，受 sum(n) 限制）。
// 算法标签：二分答案、贪心
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;
#define N 100000 + 10000
#define M 1000 + 100

ll t;
ll n, m;
ll a[N];
ll b[N];
ll mx;

int check(ll cnt) {
    ll res = 0;
    for (ll i = 1; i <= n; i++) {
        b[i] = cnt / a[i] + (cnt % a[i] != 0);
    }
    for (ll i = 1; i <= n - 1; i++) {
        if (b[i] <= 0) {
            res++; // 直接走到下一个点
            continue;
        }
        res += 2 * b[i] - 1;
        b[i + 1] -= (b[i] - 1);
    }
    if (b[n] > 0) res += 2 * b[n] - 1;
    if (res > m) return 0;
    return 1;
}

int main() {
    scanf("%lld", &t);
    while (t--) {
        mx = 0;
        scanf("%lld %lld", &n, &m);
        for (ll i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            mx = (a[i] > mx) ? a[i] : mx;
        }
        ll l = 0, r = mx * m;
        while (l < r) {
            ll mid = (r + l + 1) / 2;
            if (check(mid)) l = mid;
            else r = mid - 1;
        }
        printf("%lld\n", l);
    }
    return 0;
}
