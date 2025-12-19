#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1005
#define MAXK 105

int n, k;
double a[MAXN], f[MAXN][MAXK]; // a[i]表示第i个单词的长度
double s[MAXN]; // s是前缀和数组

int main() {
    scanf("%d%d", &n, &k);
    double ave = 0.0; // 记录平均数
    for (int i = 1; i <= n; i++) {
        char str[25];
        scanf("%s", str); // 读入单词（全是x）
        a[i] = strlen(str); // 记录单词长度
        ave += a[i]; // 累加起来好算平均数
        s[i] = (i > 0) ? s[i-1] + a[i] : a[i]; // 计算前缀和，注意i=1时的特殊处理
    }
    ave /= k; // 算出平均数

    // 初始化动态规划数组
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            f[i][j] = INT_MAX; // 初始化成最大值
        }
        f[i][1] = (s[i] - ave * i) * (s[i] - ave * i) / i; // 分成一段的最小值直接计算出方差
    }

    // 动态规划求解
    for (int j = 2; j <= k; j++) { // 分成一段不用处理了，直接从分成两段开始处理
        for (int i = j; i <= n; i++) { // 前面i个数最多也只能分成i段
            for (int l = 1; l < i; l++) { // 枚举分割点
                f[i][j] = fmin(f[i][j], f[l][j-1] + (s[i] - s[l] - ave * (i - l)) * (s[i] - s[l] - ave * (i - l)) / (i - l));
            }
        }
    }

    printf("%.1lf\n", f[n][k]); // 输出即可

    return 0;
}
