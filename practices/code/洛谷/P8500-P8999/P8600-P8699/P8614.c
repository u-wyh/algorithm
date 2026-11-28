// https://www.luogu.com.cn/problem/P8614
// 题意：求长度为 n、各项之和为 s、且相邻后项总是比前项增加 a
// 或减少 b 的整数数列种类数，结果对 100000007 取模。
// 数据范围：100% 数据满足 1 <= n <= 1000，
// -10^9 <= s <= 10^9，1 <= a, b <= 10^6。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划、同余
#include <stdio.h>
#define mod 100000007
typedef long long ll;

int n, s, a, b;
int dp[1007][1007];

int c(int x) {
    return (x % n + n) % n;
}

int main() {
    scanf("%d %d %d %d", &n, &s, &a, &b);
    dp[0][0] = 1;

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dp[i][j] = (dp[i - 1][c(j - a * i)] + dp[i - 1][c(j + b * i)]) % mod;
        }
    }

    printf("%d\n", dp[n - 1][c(s)]);
    return 0;
}
