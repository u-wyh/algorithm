// https://www.luogu.com.cn/problem/P7777
// 题意：T 组数据，共 n 堆石子（1..n），
// 每次可花 i*p 取第 i 堆或花 |i-j|*q 取第 i, j 两堆，
// 求取完所有石子的最小总代价。
// 数据范围：1 <= T <= 10^6，1 <= n <= 10^9，
// 0 <= p, q <= 100。
// 难度评分：1200（洛谷分级换算）
// 算法标签：数学、贪心
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

ll p, q, n;

void sol() {
    scanf("%lld%lld%lld", &n, &p, &q);
    if (p == 0) {
        printf("0\n");
        return;
    }
    if (n == 1) {
        printf("%lld\n", p);
        return;
    }
    ll x = q / p;
    x = (x - 1) / 2;
    ll res = n - x;
    ll ans = 0;
    if (res % 2) {
        x++;
        res--;
    }
    ans = x * p;
    ans += (x - 1) * x * p / 2;
    ans += (res / 2) * q;
    printf("%lld\n", ans);
}

int main() {
    //freopen("tmp.in", "r", stdin);
    //freopen("tmp.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--) {
        sol();
    }
    return 0;
}
