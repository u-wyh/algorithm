// https://www.luogu.com.cn/problem/P1358
// 题意：有 n 张互不相同的牌。
// 给 m 个人分别发 a[i] 张，同一个人手里的牌不分顺序。
// 求不同发牌方案数，对 10007 取模。
// 数据范围：1 ≤ n ≤ 10000，1 ≤ m ≤ 100，
// 0 ≤ a[i] ≤ 100。
// 难度评分：1100（洛谷分级换算）
// 算法标签：组合数学、递推

#include <stdio.h>

#define MOD 10007

long long n, m, s = 1, t;
long long a[10005][105];

int main() {
    scanf("%lld %lld", &n, &m);
    a[0][0] = 1;

    // 初始化组合数数组（Pascal's Triangle Modulo）
    for (int i = 1; i <= 10000; i++) {
        for (int j = 0; j <= 100; j++) {
            if (j == 0) {
                a[i][j] = a[i-1][j]; // 第一列总是1
            } else {
                a[i][j] = (a[i-1][j-1] + a[i-1][j]) % MOD;
            }
        }
    }

    // 根据输入进行计算
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &t);
        s = (s * a[n][t]) % MOD;
        n -= t; // 牌已经被抽走了，要减掉
    }

    printf("%lld\n", s);
    return 0;
}
