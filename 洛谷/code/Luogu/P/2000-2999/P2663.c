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
