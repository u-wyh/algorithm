#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 20
#define MAX_STATES (1 << N)

int n, m, k;
int dp[MAX_STATES];
int v[N + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(dp, INT_MAX, sizeof(dp));

    for (int i = 1; i <= n; ++i) {
        int h = 0;
        for (int j = 1; j <= k; ++j) {
            int p;
            scanf("%d", &p);
            p--; // 调整为0基索引
            h |= (1 << p); // 使用位或操作符来合并状态
        }
        dp[h] = 1; // 这些口味都可以用一包糖解决
        v[i] = h; // 记录每种糖的状态
    }

    for (int i = 0; i < (1 << m); ++i) { // 枚举所有可能的状态
        for (int j = 1; j <= n; ++j) {
            if (dp[i] != INT_MAX) { // 只更新可达状态
                dp[i | v[j]] = min(dp[i | v[j]], dp[i] + 1); // 更新状态转移
            }
        }
    }

    if (dp[(1 << m) - 1] == INT_MAX) {
        printf("-1\n"); // 搭配不出来
    } else {
        printf("%d\n", dp[(1 << m) - 1]); // 搭配出来
    }

    return 0;
}
