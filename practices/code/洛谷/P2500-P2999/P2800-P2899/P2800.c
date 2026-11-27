// https://www.luogu.com.cn/problem/P2800
// 题意：输入锁妖塔层数 n，以及从下往上第 1 到第 n 层每层的高度 h_i。
// 从地面出发到达第 n 层（塔顶），每层可花费 h_i 时间爬上去，
// 或用一次仙术不耗时向上跳 1 层或 2 层。
// 每次使用仙术跳跃后必须至少再爬过一层休息，才能再次使用仙术。
// 输出一行一个整数，表示爬上塔顶的最短时间。
// 数据范围：对于 100% 的数据，1 <= n <= 10^6，
// 1 <= h_i <= 100。
// 算法标签：动态规划
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
