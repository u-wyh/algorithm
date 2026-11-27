// https://www.luogu.com.cn/problem/P2327
// 题意：N*2 扫雷棋盘，第一列每格至多 1 颗雷，第二列无雷但给出 8 连通雷数。
// 求第一列雷的合法摆放方案数。
// 输出方案数。
// 数据范围：1 <= N <= 10000。
#include <stdio.h>
// 算法标签：枚举、递推

int i, j, k, m, n, ans = 2, a[10001], b[10001];

void checkx() {
    for (i = 2; i <= n + 1; i++) {
        b[i] = a[i - 1] - b[i - 1] - b[i - 2];
        if (b[i] != 1 && b[i] != 0) {
            ans--;
            break;
        }
        if (i == n + 1 && b[i] != 0) {
            ans--;
            break;
        }
    }
}

int main() {
    scanf("%d", &n);
    b[0] = 0;
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    b[1] = 1;
    checkx();
    b[1] = 0;
    checkx();
    printf("%d\n", ans);
    return 0;
}
