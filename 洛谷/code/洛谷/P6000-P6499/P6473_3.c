// https://www.luogu.com.cn/problem/P6473
// 题意：匀速以每年 v 的速度推石上长 L 的山坡，
// 有 n 个位于 a_i 的魔法，
// 若施展某魔法则首次到达 a_i 时立即滚回山底重新推起。
// q 次询问 t_i，
// 求最少施展几个魔法才能使到达山顶用时严格大于 t_i（无法做到输出 -1）。
// 数据范围：1 <= n, q <= 2*10^5，
// 1 <= v <= L <= 10^9，
// 1 <= a_i < L（a_i 互不相同）
// 1 <= t_i <= 10^9。
// 算法标签：二分查找、前缀和、排序
#include <stdio.h>
#include <stdlib.h>

double b[200001], a[200001];
long long n;
double l, v, q, t;

// 自定义比较函数，用于qsort
int cmp(const void *x, const void *y) {
    double dx = *(double *)x;
    double dy = *(double *)y;
    return (dx > dy) - (dx < dy); // 简化比较
}

int main() {
    // freopen("endless.in", "r", stdin);
    // freopen("endless.out", "w", stdout);

    scanf("%lld %lf %lf", &n, &l, &v);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &a[i]);
    }

    // 使用qsort从大到小排序
    qsort(a, n, sizeof(double), cmp);

    b[0] = l / v; // 不使用魔法的时间
    for (int i = 1; i < n; i++) {
        b[i] = a[i] / v + b[i - 1]; // 使用前i项魔法的时间
    }

    scanf("%lf", &q);
    while (q--) {
        scanf("%lf", &t);
        if (b[n - 1] <= t) {
            printf("-1\n");
            continue;
        }

        int l = 0, r = n - 1, ans = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (b[mid] > t) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
