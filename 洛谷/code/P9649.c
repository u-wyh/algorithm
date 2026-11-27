// https://www.luogu.com.cn/problem/P9649
// 题意：多组数据（共 T 组）。给定 n 个整数区间 [l_i, r_i]，从每个区间中各选一个整数，最大化这 n 个整数按位与（AND）的结果。
// 题意：第一行输入 T，每组输入 n 及 n 行 (l_i, r_i)；每组输出一行一个整数。
// 数据范围：1 <= n <= 10^5，0 <= l_i <= r_i <= 10^9，sum(n) <= 10^6（未显式给出 T 上界
// 受 sum(n) 限制）。
// 算法标签：按位贪心
#include <stdio.h>
#include <ctype.h>

#define ll long long

int read() {
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

#define maxN 100005

int T, n;
ll ans;
int L[maxN], R[maxN];

int cal(int x, int i) {
    if (!((x >> i) & 1))
        x = ((x >> i) | 1) << i;
    return x;
}

int main() {
    T = read();
    while (T--) {
        ans = 0;
        n = read();
        for (int i = 1; i <= n; i++) {
            L[i] = read();
            R[i] = read();
        }
        for (int i = 30; i >= 0; i--) {
            ll d = 1ll << i;
            int flag = 0;
            for (int j = 1; j <= n; j++) {
                if (cal(L[j], i) > R[j]) {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                continue;
            for (int j = 1; j <= n; j++) {
                L[j] = cal(L[j], i);
            }
            ans |= d;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
