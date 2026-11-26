// https://www.luogu.com.cn/problem/P1435
// 题意：输入一个区分大小写的字符串。
// 每次可在任意位置插入一个字符，使其最终变成回文串。
// 输出变成回文串所需插入的最少字符数。
// 数据范围：
// 0 < l <= 1000（字符串长度）
#include <stdio.h>
#include <string.h>
#include <limits.h> // 用于INT_MAX

#define MAX_LEN 1200

int f[2][MAX_LEN];
char s[MAX_LEN];

// 自定义的min函数，因为C标准库中没有直接返回两个整数中较小值的函数
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%s", s + 1); // 从s[1]开始读入字符串，s[0]未使用
    int len = strlen(s + 1);
    int now = 0;

    // 初始化f数组，这里假设所有子串的初始最小插入次数为非常大的数（INT_MAX）
    // 除了f[0][0]为0（空字符串不需要插入）
    for (int i = 0; i <= len; i++) {
        f[0][i] = INT_MAX;
    }
    f[0][0] = 0;

    // 动态规划过程
    for (int i = len - 1; i >= 1; i--) {
        for (int j = i + 1; j <= len; j++) {
            if (s[i] == s[j]) {
                f[now ^ 1][j] = f[now][j - 1];
            } else {
                f[now ^ 1][j] = min(f[now][j], f[now ^ 1][j - 1]) + 1;
            }
        }
        now ^= 1;
    }

    // 输出结果，注意结果存储在f[now][len]中
    printf("%d\n", f[now][len]);

    return 0;
}
