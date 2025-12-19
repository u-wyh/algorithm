#include <stdio.h>
#include <string.h>
#include <limits.h> // 用于初始化dp数组为最大值

int main() {
    int n, i, j, k, l, t;
    char s[60];
    int dp[60][60]; // 注意这里dp数组的类型已经是int，无需再次声明

    scanf("%s", s);
    n = strlen(s);
    //printf("%d\n",n);

    // 初始化dp数组
    for (i = 0; i < n; ++i) {
        for (j = 0; j <= i; ++j) { // 注意这里j的上限是i，因为dp[i][j]只有在j<=i时才有意义
            dp[i][j] = (j == i) ? 1 : INT_MAX; // 如果i==j，则长度为1的子串可以分割成1个部分
        }
    }

    // 动态规划计算
    for (l = 1; l < n; ++l) {
        for (i = 0; i + l < n; ++i) {
            int r = i + l; // 右边界
            if (s[i] == s[r]) {
                dp[i][r] = dp[i][r - 1]; // 如果首尾字符相等，则当前子串的分割数与前一个子串相同
            } else {
                dp[i][r] = dp[i][i] + dp[i + 1][r]; // 初始化为不分割的情况
                for (k = i + 1; k < r; ++k) {
                    dp[i][r] = (dp[i][r] < dp[i][k] + dp[k + 1][r]) ? dp[i][r] : dp[i][k] + dp[k + 1][r];
                }
            }
        }
    }

    printf("%d\n", dp[0][n - 1]); // 输出结果
    return 0;
}
