// https://www.luogu.com.cn/problem/P1031
// 题意：有 N 堆纸牌排成一行，第 i 堆初始有 A[i] 张。一次从某堆取若干张纸牌，移到相邻一堆。求让所有堆的纸牌数相等所需的最少移动次数。
// 数据范围：1 ≤ N ≤ 100，1 ≤ A[i] ≤ 10000。
// 算法标签：贪心

#include <stdio.h>

int n, a[101], mid, all, ans;

int main() {
    scanf("%d", &n);
    all = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        all += a[i];
    }
    all /= n;

    ans = 0;
    for (int i = 1; i < n; i++) { // 注意循环到n-1，以避免访问a[n+1]
        if (a[i] != all) {
            a[i + 1] += a[i] - all;
            ans++;
        }
    }

    printf("%d", ans);
    return 0;
}
