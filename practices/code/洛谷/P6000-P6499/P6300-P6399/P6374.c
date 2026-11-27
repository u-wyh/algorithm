// https://www.luogu.com.cn/problem/P6374
// 题意：给定一棵 n 个点的无根树，q 次询问每次给 (a, b, c)，
// 求有多少个节点 i 满足以 i 为根时 a 和 b 的 LCA 恰好为 c。
// 数据范围：1 <= n <= 5*10^5，1 <= q <= 2*10^5。
// 算法标签：数学、分类讨论
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef long long LL;

LL max(LL a, LL b) {
    return a > b ? a : b;
}

LL min(LL a, LL b) {
    return a < b ? a : b;
}

int main(void) {
    LL a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    LL x = max(a, b), y = min(a, b);
    LL m = x - y;

    if (m > c) { // 如果 x-y>c, 即 c+y>x，那就是分类讨论时的第一种情况。
        LL ans = (LL)((LL)(floor(sqrt(8 * (y + c) + 1))) - 1) / 2; // 套公式
        printf("%lld\n", ans);
        return 0;
    } else { // 否则那就是第二种情况
        c -= m;
        LL ans = (LL)((LL)(floor(sqrt(8 * (x + (LL)(c / 2)) + 1))) - 1) / 2; // 套公式
        printf("%lld\n", ans);
    }

    return 0;
}
