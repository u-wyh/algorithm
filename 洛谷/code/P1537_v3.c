#include <stdio.h>
#include <string.h>

#define MAX_VALUE 6  // 最大弹珠价值
#define MAX_SUM (2 * 10000 * 6)  // 假设最大总和不超过 2 * 10^4 * 6

int dp[MAX_SUM + 1];  // 动态规划数组，用于记录是否可以组成某个和
int a[MAX_VALUE + 1];  // 存储每种价值弹珠的数量

int main() {
    int Case = 0;
    while (1) {
        Case++;
        int sum = 0;
        for (int i = 1; i <= 6; i++) {
            scanf("%d", &a[i]);
            sum += i * a[i];
        }
        if (sum == 0) break;  // 结束条件

        printf("Collection #%d:\n", Case);
        if (sum % 2 != 0) {
            printf("Can't be divided.\n\n");
            continue;
        }

        memset(dp, 0, sizeof(dp));  // 初始化dp数组
        dp[0] = 1;  // 初始状态，和为0时总是可以组成的

        for (int i = 1; i <= 6; i++) {
            for (int j = sum / 2; j >= i; j--) {
                for (int k = 1; k <= a[i] && j >= k * i; k++) {
                    dp[j] |= dp[j - k * i];
                }
            }
        }

        if (dp[sum / 2]) {
            printf("Can be divided.\n\n");
        } else {
            printf("Can't be divided.\n\n");
        }
    }

    return 0;
}
