// https://www.luogu.com.cn/problem/P2904
// 题意：输入奶牛数 N、约翰独自划船单程过河耗时 M，以及木筏上增加第 i 头牛额外增加的耗时 M_i。
// 约翰必须一直在木筏上；载 k 头牛过河耗时为 M + sum_{i=1..k} M_i 分钟，约翰独自划船返回耗时为 M 分钟。
// 合理规划分批渡河方式，将所有 N 头牛运到对岸。
// 输出一行一个整数，表示让所有奶牛过河的最短总时间。
// 数据范围：对于 100% 的数据，1 <= N <= 2500，1 <= M <= 1000，1 <= M_i <= 1000。
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
