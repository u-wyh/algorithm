// https://www.luogu.com.cn/problem/P8786
// 题意：输入整数 N 和 M；
// 初始有 2 斗酒，依次经历 N 次遇店（酒量翻倍，0 斗翻倍仍为 0）和 M 次遇花（喝 1 斗，0 斗时遇花非法）
// 要求最后一次是遇花且恰好喝光为 0 斗，输出合法的遇店与遇花顺序种数对 10^9+7 取模的结果。
// 数据范围：1 <= N, M <= 100。
// 算法标签：动态规划
#include <stdio.h>

#define MOD 1000000007

int n, m;
int f[205][105][105];

int main() {
    scanf("%d %d", &n, &m);
    f[0][0][2] = 1; // 初始化条件

    for (int i = 0; i < n + m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k <= m; k++) {
                if (f[i][j][k]) {
                    if (k > 0) {
                        f[i + 1][j + 1][k - 1] = (f[i + 1][j + 1][k - 1] + f[i][j][k]) % MOD;
                    }
                    if (k <= 50) {
                        f[i + 1][j][k * 2] = (f[i + 1][j][k * 2] + f[i][j][k]) % MOD;
                    }
                }
            }
        }
    }

    printf("%d\n", f[n + m][m][0]);
    return 0;
}
