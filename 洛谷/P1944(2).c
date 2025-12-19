#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 1000005

char s[L];
int l, f[L], Ans = 0, id = 0;

int main() {
    scanf("%s", s + 1); // 输入，下标从1开始
    l = strlen(s + 1); // 下标从1开始的字符串长度
    for (int i = 2; i <= l; ++i) { // s[1]显然无法匹配，所以从2开始
        if (s[i] == '(' || s[i] == '[') continue; // 如分析
        else if ((s[i] == ')' && s[i - f[i - 1] - 1] == '(') ||
                 (s[i] == ']' && s[i - f[i - 1] - 1] == '[')) {
            f[i] = f[i - 1] + 2 + (i - f[i - 1] > 2 ? f[i - f[i - 1] - 2] : 0);
            // 注意处理i-f[i-1]-2可能越界的情况
            if (f[i] > Ans) {
                Ans = f[i];
                id = i; // Ans记录最长括号匹配，id记录最长括号匹配的下标
            }
        }
    }
    for (int i = id - Ans + 1; i <= id; ++i) {
        printf("%c", s[i]);
    }
    putchar('\n');
    return 0;
}
