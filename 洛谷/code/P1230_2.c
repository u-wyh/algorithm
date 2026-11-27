// https://www.luogu.com.cn/problem/P1230
// 题意：初始奖励 m 元，共 n 个时段和 n 个小游戏（每个需占 1 个整时段完成）。
// 题意：游戏 i 需在期限 t_i 前完成，否则从奖金中扣除 w_i 元（不会扣成负值赔钱）。
// 题意：合理安排做游戏的顺序，求能赢取的最大金额。
// 输入：第一行 m，第二行 n，第三行 n 个数表期限 t_i，第四行 n 个数表扣款 w_i。
// 输出：一行输出能赢取的最多的钱。
// 数据范围：1 <= n <= 500，1 <= m <= 5 * 10^5。
// 数据范围：1 <= t_i <= n，1 <= w_i <= 1000。
#include <stdio.h>
#include <stdlib.h>
// 算法标签：贪心、排序

typedef struct {
    int t, val;
} ben;

ben a[505];
int vis[505];

// 比较函数，用于qsort
int cmp(const void *a, const void *b) {
    ben *x = (ben *)a;
    ben *y = (ben *)b;
    return y->val - x->val; // 降序排序
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i].t);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i].val);
    }

    // 使用qsort进行排序
    qsort(a, n, sizeof(ben), cmp);

    int ans = 0, t = 0;
    for (int i = 0; i < n; i++) {
        int tag = 0;
        for (int j = a[i].t; j > 0; j--) {
            if (vis[j] == 0) {
                vis[j] = 1;
                tag = 1;
                break;
            }
        }
        if (tag == 0) {
            ans += a[i].val;
        }
    }

    printf("%d\n", m - ans);
    return 0;
}
