// https://www.luogu.com.cn/problem/P10155
// 题意：给 1 到 n 的一个排列。
// 一次操作可选位置 i，找到它右侧第一个比它大的数，
// 再把原来 i 处的数挪到那个数之前。
// 求排成升序的最少操作次数，无解输出 -1。
// 数据范围：1 ≤ n ≤ 2 × 10^6，每个数 1 到 n 恰好出现一次。
// 算法标签：贪心、后缀最小值

#include <stdio.h>

#define NN 2000004 // 定义数组大小

int a[NN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    if (a[n] != n) {
        printf("-1\n");
        return 0;
    }
    int minn = 1e9, ans = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] < minn) {
            minn = a[i];
        } else {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
