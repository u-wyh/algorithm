#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // 为了使用INT_MAX

#define MAX_N 1000010

long long a[MAX_N];

// 用于qsort的比较函数
int compare(const void *a, const void *b) {
    long long arg1 = *((long long*)a);
    long long arg2 = *((long long*)b);
    if (arg1 > arg2) return -1;
    if (arg1 < arg2) return 1;
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    // 读取数组
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    // 使用qsort排序
    qsort(a + 1, n, sizeof(long long), compare);

    // 限制n的大小
    n = (n > 32) ? 32 : n;

    long long mx = 0;

    // 计算最大值
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            mx = (mx > (a[i] & a[j])) ? mx : (a[i] & a[j]);
        }
    }

    printf("%lld\n", mx);

    return 0;
}
