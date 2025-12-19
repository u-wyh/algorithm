#include<stdio.h>
#include<limits.h> // 用于定义INT_MAX

int n, k, x, dp[4009];

int min(int a,int b)
{
    return a<b?a:b;
}

int main() {
    scanf("%d %d %d", &n, &k, &x);
    for (int i = 0; i <= 4000; i++) {
        dp[i] = INT_MAX; // 初始化为无穷大，表示不可达
    }
    dp[x] = 0; // 初始状态，一场比赛都不打

    while (n--) {
        int id, a;
        scanf("%d %d", &id, &a);
        int m = 4000;
        if (id == 2)
            m = 1899; // 参与比赛的比赛分限制

        // 正向遍历
        for (int i = a + 1; i <= m; i++) {
            int now = i - (i - a + 3) / 4; // 计算打完后的分数
            if (now <= 4000 && dp[i] != INT_MAX) { // 确保now在范围内且dp[i]有效
                dp[now] = (dp[now] < dp[i] + 1) ? dp[now] : dp[i] + 1; // 尝试更新
            }
        }

        // 反向遍历
        for (int i = min(m, a - 1); i >= 0; i--) {
            int now = i + (a - i) / 4;
            if (now <= 4000 && dp[i] != INT_MAX) { // 确保now在范围内且dp[i]有效
                dp[now] = (dp[now] < dp[i] + 1) ? dp[now] : dp[i] + 1; // 尝试更新
            }
        }
    }

    // 查找答案
    for (int i = 4000; i >= 0; i--) {
        if (dp[i] <= k) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}

