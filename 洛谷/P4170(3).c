#include<stdio.h>
#include<string.h>
#include<limits.h>
#define Max 51

static int dp[Max][Max];

int min(int a, int b) {
    return a < b ? a : b;
}

int compute(char *s, int n) {
    // 初始化长度为1和2的子串的dp值
    for (int i = 0; i < n - 1; i++) {
        dp[i][i] = 1;
        dp[i][i + 1] = (s[i] == s[i + 1]) ? 1 : 2;
    }

    // 填充dp数组
    for (int len = 3; len <= n; len++) { // 从长度为3的子串开始处理
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i][j - 1]; // 如果两端相同，则继承左半部分的结果
            } else {
                dp[i][j] = INT_MAX; // 初始化为最大值，用于找最小值
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    char s[Max];
    fgets(s, Max, stdin);
    // 去除fgets读取的换行符
    s[strcspn(s, "\n")] = 0;
    int n = strlen(s);
    printf("%d\n", compute(s, n));
    return 0;
}
