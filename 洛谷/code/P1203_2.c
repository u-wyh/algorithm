// https://www.luogu.com.cn/problem/P1203
// 题意：给定环形项链上 n 颗珠子的颜色序列（r 红、b 蓝、w 白）。
// 题意：从某处打断展开成链，分别从两端收集同色珠子（白色可按红或蓝算，两端独立）。
// 题意：求能收集到的最大珠子总数（同一颗珠子不能重复收集）。
// 输入：第一行输入珠子数 n，第二行输入长度为 n 的 r/b/w 字符串。
// 输出：一行输出能收集到的最大珠子数量。
// 数据范围：3 <= n <= 350。
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

// 定义max和min函数
int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    char s[700], c;
    int a = 0, b = 0, w = 0, ans = 0;

    scanf("%d%s", &n, s);

    // 复制字符串以处理循环
    char temp[700 * 2];
    memcpy(temp, s, n);
    memcpy(temp + n, s, n);

    // 初始化c为第一个字符
    c = s[0];

    // 遍历两倍长度的字符串
    for (int i = 0; i < n * 2; i++) {
        if (temp[i] == 'w') {
            b++;
            w++;
        } else if (temp[i] == c) {
            b++;
            w = 0;
        } else {
            ans = max(ans, a + b);
            a = b - w;
            b = w + 1;
            w = 0;
            c = temp[i];
        }
    }

    // 最后一次更新ans
    ans = max(ans, a + b);

    // 输出结果，但不超过n
    printf("%d\n", min(ans, n));

    return 0;
}
