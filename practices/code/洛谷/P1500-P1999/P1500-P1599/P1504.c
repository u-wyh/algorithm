// https://www.luogu.com.cn/problem/P1504
// 题意：给 n 座积木城堡，可从每座选一些原有积木留下。
// 城堡高度是留下的积木棱长之和。
// 要求所有城堡最后等高，输出最大的共同高度，无法保留正高度则输出 0。
// 数据范围：1 ≤ n ≤ 100，每座积木至多 100 块，
// 棱长在 [0,100]，每座输入以 -1 结束。
// 难度评分：1300（洛谷分级换算）
// 算法标签：背包动态规划

#include <stdio.h>
#include <string.h>

#define MAX_N 1001
#define MAX_SUM 100001

int n, maxn, x, g, sum;
int a[MAX_N];
int ans[MAX_SUM];
int f[MAX_SUM];

int main() {
    scanf("%d", &n);
    maxn = 0;
    memset(ans, 0, sizeof(ans));

    for (int k = 1; k <= n; k++) {
        memset(f, 0, sizeof(f));
        g = 0;
        sum = 0;

        while (1) {
            scanf("%d", &x);
            if (x < 0) break;
            a[++g] = x;
            sum += x;
        }

        f[0] = 1;
        a[0] = g;

        if (sum > maxn) maxn = sum;

        for (int i = 1; i <= g; i++) {
            for (int j = sum; j >= a[i]; j--) {
                if (f[j - a[i]] && !f[j]) {
                    f[j] = 1;
                    ans[j]++;
                }
            }
        }
    }

    for (int i = maxn; i >= 0; i--) {
        if (ans[i] == n) {
            printf("%d", i);
            return 0;
        }
    }

    printf("0");
    return 0;
}
