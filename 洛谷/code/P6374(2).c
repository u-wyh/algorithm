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
