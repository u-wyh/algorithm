// https://www.luogu.com.cn/problem/P1970
// 题意：给定 n 朵花的高度，删去任意一些花而保持剩余花的顺序。要求相邻高度严格交替升降，可以先升也可以先降，单朵也合法。求最多可保留多少朵。
// 数据范围：1 ≤ n ≤ 10^5，0 ≤ h_i ≤ 10^6。
// 算法标签：贪心

#include <stdio.h>

#define MAX_N 1000005

int n, h[MAX_N], ans = 1;
int con = 0; // 使用整型代替布尔型

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }

    if (h[2] >= h[1]) {
        con = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (con == 0 && i == n) {
            ans++;
            break;
        }

        if (con == 1) {
            if (h[i + 1] < h[i]) {
                ans++;
                con = 0;
                continue;
            }
        }

        if (con == 0) {
            if (h[i + 1] > h[i]) {
                ans++;
                con = 1;
                continue;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}
