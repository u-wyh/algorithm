#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n;
int a[100005];
int x = 0;

// 自定义int数组的比较函数
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// 自定义max函数
int max(int a, int b) {
    return (a > b) ? a : b;
}

int ansmin() {
    if ((a[n-2] - a[0] == n-2 && a[n-1] - a[n-2] > 2) ||
        (a[n-1] - a[1] == n-2 && a[1] - a[0] > 2)) {
        // 特判，条件同上
        return 2;
    }
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < n-1 && a[j+1] - a[i] <= n-1) {
            j++;
        }
        x = (x > j-i+1) ? x : j-i+1;
    }
    return n - x;
}

int ansmax() {
    return (max(a[n-2] - a[0], a[n-1] - a[1]) - n + 2);
    // 注意：C语言中没有max函数，需要自己定义或使用条件运算符
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), cmp);
    printf("%d\n%d\n", ansmin(), ansmax());
    return 0;
}

