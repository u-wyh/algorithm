#include<stdio.h>
#include<limits.h> // 用于INT_MAX

#define MAX_N 10010

int f[MAX_N];
int sum[MAX_N];
int w[MAX_N];
int m, n;

int main() {
    scanf("%d %d", &n, &m);
    int inf = INT_MAX; // 使用INT_MAX作为无限大
    for (int i = 1; i <= n; i++) {
        f[i] = inf; // 初始化f[i]为无限大
        scanf("%d", &w[i]);
        if (i > 1) {
            sum[i] = sum[i - 1] + w[i]; // 计算前缀和，注意i>1时才开始累加
        } else {
            sum[i] = w[i]; // 第一个元素的前缀和就是它本身
        }
    }
    for (int i = 1; i <= n; i++) {
        sum[i] += 2 * m; // 每个元素加上2*m
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (f[j - i] != inf) { // 确保f[j-i]不是无限大才进行更新
                f[j] = (f[j] < f[j - i] + sum[i]) ? f[j] : f[j - i] + sum[i]; // 更新f[j]
            }
        }
    }

    if (f[n] == inf) {
        printf("No solution\n"); // 如果没有找到可行解
    } else {
        printf("%d\n", f[n] - m); // 输出解，减去m因为不需要划回来
    }

    return 0;
}
