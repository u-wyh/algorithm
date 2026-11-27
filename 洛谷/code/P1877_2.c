// https://www.luogu.com.cn/problem/P1877
// 题意：给定初始音量和 n 次调整量。每次必须选择加上或减去本次调整量，调整后的音量始终在 [0,maxLevel]。
// 求最后一首歌的最大音量，无解输出 -1。
// 数据范围：1 ≤ n ≤ 50，1 ≤ maxLevel ≤ 1000，0 ≤ beginLevel ≤ maxLevel
// 1 ≤ c_i ≤ maxLevel。
// 算法标签：动态规划

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
