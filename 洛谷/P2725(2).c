#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_VALUE 2000000
#define LL unsigned long long

int k, n, i, j, s, a; // k: 总共消耗的邮票数
int f[MAX_VALUE + 1]; // f[i]表示构成面值为i至少需要的邮票数

// 自定义min函数
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d%d", &k, &n);
    for (i = 0; i <= MAX_VALUE; i++) {
        f[i] = MAX_VALUE + 1; // 标记为不可达
    }
    f[0] = 0; // 赋初值，用0张邮票可以构成0

    for (i = 1; i <= n; i++) {
        scanf("%d", &a); // 读入邮票面值
        for (j = a; j <= MAX_VALUE; j++) {
            if (f[j - a] + 1 <= k) { // 用的邮票数目在范围内
                f[j] = min(f[j], f[j - a] + 1); // 取较小的
            }
        }
    }

    s = 0;
    for (i = 1; i <= MAX_VALUE; i++) { // 找从1开始连续的能取的集合的最后一个
        if (f[i] == MAX_VALUE + 1) { // 凑不出了
            s = i - 1; // 记录
            break; // 退出
        }
    }

    printf("%d\n", s); // 输出
    return 0;
}
