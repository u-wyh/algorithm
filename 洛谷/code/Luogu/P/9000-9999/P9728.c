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
