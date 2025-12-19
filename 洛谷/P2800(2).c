#include <stdio.h>
#include <limits.h> // 用于INT_MAX

#define MAX_N 1000005

int min(int a,int b)
{
    return a<b?a:b;
}

int n;
int a[MAX_N];
int f[MAX_N + 1]; // 注意这里加了1，因为要访问f[n+1]

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        f[i] = INT_MAX; // 注意初始化
    }
    f[n + 1] = INT_MAX; // 同样初始化f[n+1]

    for (int i = 1; i <= n + 1; i++) { // 循环到n+1
        // 注意这里i从1开始，但是数组a[i]只定义到n，所以a[i]在i=n+1时未定义，但f[i]的计算不需要a[n+1]
        f[i] = INT_MIN; // 理论上应该使用一个很大的数作为初始值，但这里为了简化逻辑，先设为最小值
        if (i >= 1) f[i] = min(f[i], f[i - 1]);
        if (i >= 2) f[i] = min(f[i], f[i - 2]);
        if (i >= 3) f[i] = min(f[i], f[i - 3]);
        if (i <= n) f[i] += a[i]; // 只在i<=n时加a[i]，因为a[n+1]未定义
    }

    // 输出解，注意f[n+1]可能仍然是INT_MAX，表示无法到达或未更新
    if (f[n + 1] == INT_MAX) {
        printf("Unreachable\n"); // 或其他表示无法到达的值
    } else {
        printf("%d\n", f[n + 1]);
    }

    return 0; // 程序结束
}
