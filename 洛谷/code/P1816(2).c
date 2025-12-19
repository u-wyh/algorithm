#include <stdio.h>
#include <limits.h> // 引入INT_MAX，用于初始化ans

int a[100001];

int main() {
    int m, n, t, k, ans;
    scanf("%d%d", &m, &n);

    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }

    // 使用INT_MAX初始化ans，因为它是C语言中int类型能表示的最大值
    ans = INT_MAX;

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &t, &k);
        ans = INT_MAX; // 每次查询前重置ans

        for (int j = t; j <= k; j++) {
            ans = (ans < a[j]) ? ans : a[j]; // 使用三元运算符进行min操作
        }

        printf("%d ", ans);
    }

    printf("\n"); // 通常在输出完成后加一个换行符
    return 0;
}
