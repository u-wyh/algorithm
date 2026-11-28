// https://www.luogu.com.cn/problem/P9975
// 题意：N 头奶牛排成一排，
// 给定长度为 N 的 01 串表示若干晚后各牛是否被感染（1 感染，0 未感染）。
// 初始有若干头牛被感染，每过一晚，
// 每头已感染的牛都会同时传染给左右紧邻的牛（若存在）。
// 求初始最少可能有多少头牛被感染。
// 题意：第一行输入 N，第二行输入长度为 N 的 01 串；输出一个整数。
// 数据范围：1 <= N <= 3 * 10^5。
// 难度评分：1200（洛谷分级换算）
// 算法标签：连续段统计
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ll long long
#define MAXN 300005

ll read() {
    char ch;
    ll f = 1, r = 0;
    ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0') {
        r = (r << 3) + (r << 1) + (ch ^ 48);
        ch = getchar();
    }
    return r * f;
}

void write(ll f) {
    if (f < 0) {
        f = -f;
        putchar('-');
    }
    if (f > 9) write(f / 10);
    putchar(f % 10 + '0');
}

int main() {
    ll n = read();
    ll a[MAXN], ans[MAXN], mn = MAXN, last = 0, cnt = 0;
    ll st[MAXN], ed[MAXN], st_size = 0, ed_size = 0;

    for (ll i = 1; i <= n; ++i) {
        a[i] = getchar() - '0';
        if (a[i]) {
            last++;
            if (!a[i - 1]) {
                st[st_size++] = i;
            }
        } else if (!a[i] && last) {
            if (st[st_size - 1] == 1) {
                mn = (mn < i - 2) ? mn : i - 2;
            } else {
                mn = (mn < (last - 1) / 2) ? mn : (last - 1) / 2;
            }
            last = 0;
            ed[ed_size++] = i - 1;
        }
    }

    if (last) {
        mn = (mn < last - 1) ? mn : last - 1;
        ed[ed_size++] = n;
    }

    for (ll i = 0; i < st_size; ++i) {
        cnt += ceil(1.0 * (ed[i] - st[i] + 1) / (2 * mn + 1));
    }

    write(cnt);
    putchar('\n');

    return 0;
}
