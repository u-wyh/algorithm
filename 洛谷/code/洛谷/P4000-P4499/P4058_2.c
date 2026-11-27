// https://www.luogu.com.cn/problem/P4058
// 题意：第一行输入树的数量 n、订单总量 S 和单块木料最小长度要求 L；
// 第二行输入初始树高 H_1..H_n，第三行输入每月生长高度 A_1..A_n。
// 只能整棵砍下长度不小于 L 的树来凑足总长度不少于 S 的木料，
// 求最少需要等待多少个月才能完成订单。
// 输出一行一个整数表示最少月数。
// 数据范围：对于全部测试点，1 <= n <= 200000，
// 1 <= S, L <= 10^{18}，
// 1 <= H_i, A_i <= 10^9。
// 算法标签：二分答案
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 200001

typedef unsigned long long ull;
typedef long long ll;

ull n, s, l;
ull h[MAXN], a[MAXN];

int read() {
    int x = 0, c = 1;
    char ch = ' ';
    while ((ch > '9' || ch < '0') && ch != '-') ch = getchar();
    if (ch == '-') c = -1, ch = getchar();
    while (ch <= '9' && ch >= '0') x = x * 10 + ch - '0', ch = getchar();
    return x * c;
}

bool check(ll x) {
    ull cnt = 0;
    for (int i = 0; i < n; i++) {
        if (h[i] + a[i] * x >= l) {
            cnt += h[i] + a[i] * x;
            if (cnt >= s) break;
        }
    }
    return cnt >= s;
}

int main() {
    scanf("%llu %llu %llu", &n, &s, &l);
    for (int i = 0; i < n; i++) h[i] = read();
    for (int i = 0; i < n; i++) a[i] = read();

    ll left = 0, right = 100000000000000000ll;
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (check(mid)) right = mid - 1;
        else left = mid + 1;
    }

    printf("%lld\n", left);
    return 0;
}
