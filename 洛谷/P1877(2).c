#include <stdio.h>
#include <stdbool.h> // 引入布尔类型

int n, begin, maxlevel;
int ans;
int a[51];
int f[51][1001]; // 使用整型数组模拟布尔值，0表示false，非0表示true

int main() {
    scanf("%d%d%d", &n, &begin, &maxlevel);
    // 初始化起始状态
    f[0][begin] = 1;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 动态规划填表
    for (int i = 1; i <= n; i++) {
        for (int j = maxlevel; j >= 0; j--) {
            f[i][j] = 0; // 初始化当前位置为false
            if (j - a[i] >= 0 && f[i-1][j-a[i]] != 0) {
                f[i][j] = 1; // 如果可以向下走，则更新状态
            }
            if (j + a[i] <= maxlevel && f[i-1][j+a[i]] != 0) {
                f[i][j] = 1; // 如果可以向上走，则更新状态
            }
        }
    }

    // 查找可达的最大高度
    for (int i = maxlevel; i >= 1; i--) {
        if (f[n][i] == 1) {
            printf("%d", i);
            return 0;
        }
    }

    printf("-1");
    return 0;
}
