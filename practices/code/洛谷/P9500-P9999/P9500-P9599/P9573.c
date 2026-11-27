// https://www.luogu.com.cn/problem/P9573
// 题意：多组数据（共 T 组）。
// 给定正整数 n, p，构造一个 1..n 的排列，
// 最大化相邻两项之和为 p 的倍数的对数。多解输出任意一种即可。
// 题意：第一行输入 T，接下来 T 行每行输入 n, p；输出 T 行排列。
// 数据范围：1 <= T <= 10^4，1 <= n <= 10^5，
// 1 <= p <= 10^8，1 <= sum(n) <= 3 * 10^5。
// 算法标签：构造、同余分类
#include <stdio.h>

int n, p;

void solve() {
    scanf("%d%d", &n, &p);
    if (n * 2 < p) {
        for (int i = 1; i <= n; i++) {
            printf("%d ", i);
        }
        printf("\n");
        return;
    }

    for (int i = 1; i * 2 < p; i++) {
        for (int j = 0; j <= n; j += p) {
            if (i + j <= n) printf("%d ", i + j);
            if (j + p - i <= n) printf("%d ", j + p - i);
        }
    }

    for (int i = p; i <= n; i += p) {
        printf("%d ", i);
    }

    if (p % 2 == 0) {
        for (int i = p / 2; i <= n; i += p) {
            printf("%d ", i);
        }
    }

    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
