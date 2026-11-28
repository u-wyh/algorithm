// https://www.luogu.com.cn/problem/P3353
// 题意：输入星星数 N、窗户宽度 W，
// 以及每颗星星的坐标 X_i 和亮度 B_i（同一坐标可能有多颗星星）。
// 在数轴上放置宽度为 W 的窗户并统计涵盖星星的亮度之和；
// W=0 时不能覆盖任何星星（答案为 0），
// W>=3 为奇数时一次可覆盖连续 W 个整点坐标。
// 输出能看到星星的最大亮度和。
// 数据范围：1 <= N <= 10^5，0 <= W <= 10^5，
// 1 <= X_i <= 10^5，1 <= B_i <= 100
// 除 W=0 外 W 均为 >=3 的奇数。
// 难度评分：900（洛谷分级换算）
// 算法标签：前缀和、滑动窗口
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000005

int f[MAX_N], sum[MAX_N], n, m, x, y, ans, maxn;

int read() {
    int x = 0;
    char c;
    int f = 0; // 0 for positive, 1 for negative

    c = getchar();
    if (c == '-') f = 1;
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
    return x;
}

typedef struct {
    int x, y;
} mmp;

int cmp(const void *a, const void *b) {
    mmp *m1 = (mmp *)a;
    mmp *m2 = (mmp *)b;
    return m1->x - m2->x;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    n = read();
    m = read();
    maxn = 1;
    for (int i = 0; i < n; i++) {
        x = read();
        y = read();
        f[x] += y;
        maxn = max(maxn, x);
    }

    for (int i = 1; i <= maxn; i++) {
        sum[i] = sum[i - 1] + f[i];
    }

    ans = -1;
    for (int i = m; i <= maxn; i++) {
        ans = max(ans, sum[i] - sum[i - m]);
    }

    printf("%d\n", ans);
    return 0;
}
