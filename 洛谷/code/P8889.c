// https://www.luogu.com.cn/problem/P8889
// 题意：输入序列 a_1..a_n 和 m 个互不相同的整数 b_1..b_m；
// 将 a 中所有等于 b 中任一元素的项删除并在该处切开，统计最终剩余的非空连续片段个数并输出。
// 数据范围：1 <= n, m <= 5*10^5，-10^18 <= a_i, b_i <= 10^18，b 中元素两两不同。
// 算法标签：排序、二分查找
#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

long long n, m, a[MAXN], b[MAXN], ans;

int compare(const void *x, const void *y) {
    long long x_val = *(long long *)x;
    long long y_val = *(long long *)y;
    return (x_val < y_val) ? -1 : (x_val > y_val);
}

int check(long long k) {
    long long l = 0, r = m - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (k < b[mid]) r = mid - 1;
        else if (k > b[mid]) l = mid + 1;
        else return 1;
    }
    return 0;
}

int main() {
    scanf("%lld %lld", &n, &m);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i < m; i++) scanf("%lld", &b[i]);

    // 注意这里要对b数组的m个元素进行排序，而不是m+1个
    qsort(b, m, sizeof(long long), compare);

    // 初始判断最后一个元素
    if (!check(a[n - 1])) ans++;

    // 遍历数组a，除了最后一个元素
    for (int i = 0; i < n - 1; i++) {
        if (!check(a[i]) && check(a[i + 1])) ans++;
    }

    printf("%lld\n", ans);
    return 0;
}
