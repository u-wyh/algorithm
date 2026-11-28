// https://www.luogu.com.cn/problem/P6069
// 题意：给定长为 n 的整数序列 a，每次可将某个元素改为任意实数，
// 求至少修改多少个元素能使序列方差不超过 m / n（输入给出 m）。
// 数据范围：1 <= n <= 2 * 10^5，1 <= m <= 10^18，
// 0 <= |a_i| <= 10^6。
// 难度评分：1400（洛谷分级换算）
// 算法标签：二分答案、前缀和、排序
#include <stdio.h>
#include <stdlib.h>

typedef long long int ll;

ll n;
double m;
ll a[200010];
ll s[200010], ps[200010];

// 自定义比较函数，用于qsort
int compare(const void *a, const void *b) {
    return (*(ll*)a - *(ll*)b);
}

int check(ll x) {
    double minn = 2e9;
    for (ll i = 1; i + x - 1 <= n; i++) {
        double p1 = ps[i + x - 1] - ps[i - 1];
        double p2 = s[i + x - 1] - s[i - 1];
        double p = p2 / x;
        double ans = p1 - 2 * p * p2 + p * p * x;
        if (ans <= m) return 1;
    }
    return 0;
}

int main() {
    scanf("%lld %lf", &n, &m);
    for (ll i = 1; i <= n; i++) scanf("%lld", &a[i]);
    qsort(a + 1, n, sizeof(ll), (int (*)(const void*, const void*))compare);

    for (ll i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i];
        ps[i] = ps[i - 1] + a[i] * a[i];
    }

    ll l = 0, r = n, mid, ans = 1;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }

    printf("%lld\n", n - ans);
    return 0;
}
