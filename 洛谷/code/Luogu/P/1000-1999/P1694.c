#include <stdio.h>
#include <stdlib.h>

int n, m, a[1005], b[1005], s[1005];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &a[i], &b[i]);
        if (a[i] > b[i]) {
            int temp = a[i];
            a[i] = b[i];
            b[i] = temp;
        }
    }

    for (int i = 1; i <= n; i++) {
        int j;
        for (j = 1; j <= 4; j++) {
            int flag = 0;
            for (int k = 1; k <= m; k++) {
                if (b[k] == i && s[a[k] - 1] == j) { // 注意数组下标从0开始，但题目中可能是从1开始考虑，这里假设题目逻辑是从1开始
                    flag = 1;
                    break;
                }
            }
            if (!flag) break;
        }
        printf("%d", j);
        s[i - 1] = j; // 同样，数组下标从0开始
        //if (i < n) printf(" "); // 如果不是最后一个数，打印空格分隔
    }
    printf("\n"); // 输出换行
    return 0;
}
