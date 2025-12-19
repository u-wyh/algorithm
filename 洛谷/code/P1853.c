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

