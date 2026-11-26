// https://www.luogu.com.cn/problem/P9728
// 题意：圆桌上按顺时针 1..n 坐着 n 位教授，面前有 1..n 个位置。
// 第 i 位教授只能拿到位置 i、前一位与后一位的菜。
// 有 a 道辣菜和 n - a 道不辣菜，每位置放一道菜。
// 能吃辣的教授（b_i = 1）满意度为拿到的所有菜数（恒为 3），不能吃辣的（b_i = 0）满意度为拿到的不辣菜数。
// 求最大总满意度。
// 题意：第一行输入 n, a，第二行输入 b_1..b_n ∈ {0, 1}；输出一行一个整数。
// 数据范围：3 <= n <= 10^5，0 <= a <= n。
#include <stdio.h>
#include <stdlib.h>

int n, a, ans, i[100005], z[100005];

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d", &n, &a);
    for (int k = 1; k <= n; k++) {
        scanf("%d", &i[k]);
    }
    i[0] = i[n];
    i[n + 1] = i[1];

    // 计算每个位置的非1邻居数量
    for (int k = 1; k <= n; k++) {
        z[k] = 0; // 初始化计数器
        for (int j = k - 1; j <= k + 1; j++) {
            // 注意数组索引可能越界，但这里通过i[0]和i[n+1]的设置避免了
            if (i[j] != 1) {
                z[k]++;
            }
        }
    }

    // 对z数组进行排序
    qsort(z + 1, n, sizeof(int), cmp);

    // 累加前a个最大的非1邻居数量
    for (int k = 1; k <= a; k++) {
        ans += z[k];
    }

    printf("%d\n", 3 * n - ans);

    return 0;
}
