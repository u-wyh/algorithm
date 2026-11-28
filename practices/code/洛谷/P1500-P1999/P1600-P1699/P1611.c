// https://www.luogu.com.cn/problem/P1611
// 题意：若将正整数 n 末尾若干位整体移到开头能变成正整数 m（均无前导 0）。
// 且 n, m 位数相同、互不相等，则称 (n, m) 为一对循环数字。
// 输入位数相同且无前导 0 的 A, B，
// 输出满足 A <= n <= m <= B 的循环数对数。
// 数据范围：
// 1 <= A, B <= 2*10^6（A, B 位数相同且无前导 0）
// 难度评分：900（洛谷分级换算）
// 算法标签：枚举、模拟
#include <stdio.h>

long long ans;
int p[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int s = 0, v = a;
    while (v) {
        v /= 10;
        s++; // 计算位数
    }

    for (int i = a; i < b; i++) { // 枚举n
        int n = i;
        int m = (n % 10) * p[s - 1] + n / 10; // 如上文计算m
        while (n != m) { // 若n == m，则m枚举完毕
            if (n < m && m <= b) { // 即符合条件，ans++
                ans++;
            }
            m = (m % 10) * p[s - 1] + m / 10; // 枚举m
        }
    }

    printf("%lld\n", ans);
    return 0;
}
