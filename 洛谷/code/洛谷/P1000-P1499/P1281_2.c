// https://www.luogu.com.cn/problem/P1281
// 题意：m 本书按顺序分给 k 人，每人抄连续且非空的一段，速度一样。
// 让每个人的抄写页数中的最大值尽量小。
// 输出各人抄写的起止书号，有多解时优先让编号靠前的人少抄。
// 数据范围：1 ≤ k ≤ m ≤ 500，每本页数在 [1,10000]。
// 算法标签：动态规划、前缀和、贪心

#include <stdio.h>
#include <string.h>

#define MAX_M 310

int n, m;
int a[MAX_M], s[MAX_M], f[MAX_M][MAX_M];


// 注意：这里需要定义 max 函数，因为C标准库中没有直接提供
int max(int a, int b) {
    return (a > b) ? a : b;
}

void dfs(int k, int t) {
    if (k == 0) return;
    if (k == 1) {
        printf("1 %d\n", t);
        return;
    }
    int p = t, s1 = a[p];
    while (s1 <= f[n][m]) {
        p--;
        s1 += a[p];
    }
    dfs(k - 1, p);
    printf("%d %d\n", p + 1, t);
}

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= m; i++) f[1][i] = s[i];

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= j - 1; k++) {
                f[i][j] = (f[i][j] < max(f[i - 1][k], s[j] - s[k])) ? f[i][j] : max(f[i - 1][k], s[j] - s[k]);
            }
        }
    }

    dfs(n, m);

    return 0;
}
