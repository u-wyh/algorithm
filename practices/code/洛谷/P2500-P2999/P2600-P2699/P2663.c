// https://www.luogu.com.cn/problem/P2663
// 题意：n 名学生（n 为偶数），第 i 名学生成绩为 a_i。
// 从中选出恰好 n/2 名学生，使其成绩和在不超过全班总分一半的前提下尽量大。
// 输出选出学生的最大成绩和。
// 数据范围：1 <= n <= 100，0 <= a_i <= 100。
// 算法标签：动态规划、0-1背包
#include <stdio.h>

int n;
int a[107];
int dp[107][10007];
int sum = 0;

int maxa(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            for (int k = sum >> 1; k >= a[i]; k--) {
                dp[j][k] = dp[j][k] | dp[j - 1][k - a[i]];
            }
        }
    }

    for (int i = sum >> 1; i >= 0; i--) {
        if (dp[n >> 1][i]) {
            printf("%d\n", i);
            return 0;
        }
    }

    // 如果没有找到解，输出0或适当的错误消息
    printf("No solution found\n");
    return 0;
}
