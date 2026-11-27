// https://www.luogu.com.cn/problem/P4343
// 题意：有 l 条按时间顺序记录的代码行数变化日志 x_i（正数表示新写 x_i 行，负数表示删去 -x_i 行，删到 0 为止）；
// 一旦代码长度 >= n 就会立刻提交 AC 一题并清空重新开始写；
// 已知一共 AC 了 k 题，求阈值 n 可能的最小值和最大值（无解输出 -1）。
// 数据范围：1 <= l <= 1e5，-1e9 <= x_i <= 1e9，k > 0 且在 int 范围内。
#include <stdio.h>
#include <stdlib.h>
// 算法标签：二分答案、贪心

#define MAX (100000 + 7)
#define LL long long

int N, k;
int a[MAX];
LL l, r, ans1 = -1, ans2 = -1;

LL work(LL im) {
    int ans = 0;
    LL sum = 0;
    for (int i = 1; i <= N; i++) {
        sum = (sum + a[i] > 0) ? sum + a[i] : 0;
        if (sum >= im) {
            sum = 0;
            ans++;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &k);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }
    l = 1;
    r = 1e18; // 注意l应设为1

    while (l <= r) {
        LL mid = (l + r) >> 1;
        if (work(mid) <= k) {
            r = mid - 1;
            if (work(mid) == k) ans1 = mid; // 注意符合条件才更新答案
        } else {
            l = mid + 1;
        }
    }

    l = 1;
    r = 1e18; // 注意l应设为1

    while (l <= r) {
        LL mid = (l + r) >> 1;
        if (work(mid) >= k) {
            l = mid + 1;
            if (work(mid) == k) ans2 = mid; // 注意符合条件才更新答案
        } else {
            r = mid - 1;
        }
    }

    if (ans1 == -1) {
        puts("-1");
    } else {
        printf("%lld %lld\n", ans1, ans2);
    }

    return 0;
}
