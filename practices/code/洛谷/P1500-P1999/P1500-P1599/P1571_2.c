// https://www.luogu.com.cn/problem/P1571
// 题意：给两份获奖编号名单，找出两份里都出现的人。
// 按他们在第一份名单里的顺序输出编号。
// 数据范围：0 ≤ n,m ≤ 10^5，编号为小于 2 × 10^9 的正整数，
// 同一份名单内无重复。
// 算法标签：二分查找、排序

#include <stdio.h>
#include <stdlib.h>

int n, m;
int a[101000], b[101000];

// 使用qsort函数对数组b进行排序
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// 二分查找的C语言实现
int binary_search(int x) {
    int l = 0, r = m - 1; // 注意C语言中数组索引从0开始
    while (l <= r) {
        int mid = (l + r) / 2;
        if (b[mid] == a[x]) return 1;
        if ((mid > 0 && b[mid - 1] < a[x] && b[mid] > a[x]) ||
            (mid < m - 1 && b[mid] < a[x] && b[mid + 1] > a[x])) return 0;
        if (b[mid] > a[x]) r = mid - 1;
        else l = mid + 1;
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]); // 注意C语言数组索引从0开始
    for (int i = 0; i < m; i++) scanf("%d", &b[i]);

    // 使用qsort对数组b进行排序
    qsort(b, m, sizeof(int), compare);

    for (int i = 0; i < n; i++) if (binary_search(i)) printf("%d ", a[i]);
    return 0;
}
