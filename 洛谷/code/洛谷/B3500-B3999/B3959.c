// https://www.luogu.com.cn/problem/B3959
// 题意：有 n 套题单，第 i 套含 a[i] 道题。
// 第 k 天要从一套还没用过的题单做 k 道，之后弃用这套。
// 输出最多能连续坚持几天。
// 数据范围：1 ≤ n ≤ 10^6，1 ≤ a[i] ≤ 10^9。
// 算法标签：贪心、排序

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, i, sum = 1;
    scanf("%d", &n);
    int a[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), compare);
    for (i = 0; i < n; i++) {
        if (a[i] < sum) {
            continue;
        } else {
            sum++;
        }
    }
    printf("%d\n", sum-1);

    return 0;
}
