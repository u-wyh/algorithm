// https://www.luogu.com.cn/problem/P1853
// 题意：给定初始资金 s 和 d 种债券，每种都有单份价格和年利息。每年可用已有资金重新配置债券，同种可买多份，利息计入下一年的资金。求 n 年后的最大资产。
// 数据范围：1 ≤ s ≤ 10^6，2 ≤ n ≤ 40，1 ≤ d ≤ 10，单份价格为不超过 10^4 的正的 1000 倍数，年利息不超过价格的 10%。

#include <stdio.h>
#include <string.h>

int m, n, d;
int w[15], v[15], f[1000005];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &m, &n, &d);
    int sum = m;
    // 初始总资产
    for (int i = 1; i <= d; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }

    for (int k = 1; k <= n; k++) {
        memset(f, 0, sizeof(f));
        // 初始状态（清零）
        for (int i = 1; i <= d; i++) { // 阶段
            for (int j = w[i] / 1000; j <= sum / 1000; j++) { // 决策
                f[j] =  max(f[j], f[j - w[i] / 1000] + v[i]) ; // 状态转移，注意处理j为0的情况
            }
        }
        sum += f[sum / 1000]; // 累加最大总资产
    }

    printf("%d\n", sum);
    return 0;
}

