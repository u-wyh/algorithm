// https://www.luogu.com.cn/problem/P3983
// 题意：第一行输入赛斯石总量 Need（单位 si），
// 第二行输入 10 个整数 a_1..a_10 分别
// 表示 1si..10si 赛斯石的市场价格。
// 可将 Need 个 1si 赛斯石任意合
// 并成若干块（重量只能为正整数，可租 1si..10si 的船运过去
// 船价为载重 1..10 对应 1, 3, 5, 7, 9, 10, 11,
// 14, 15, 17 元；
// 不计返程），使总盈利（总售价减去租船总费用）最大。
// 输出最大总盈利。
// 数据范围：所有输入数据均为正整数且在区间 (0, 10^5) 内，
// 保证最大总盈利为正。
// 难度评分：1500（洛谷分级换算）
// 算法标签：完全背包、动态规划
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll f[20], n, m, a[20], v[20] = {0, 1, 3, 5, 7, 9, 10, 11, 14, 15, 17}; // v数组储存租每艘船的费用
ll dp[100010], ans = 0;

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= 10; i++) {
        scanf("%lld", &a[i]);
    }

    // 计算每艘船的最大总收益
    for (int i = 1; i <= 10; i++) {
        for (int j = i; j <= 10; j++) {
            f[j] = (f[j - i] + a[i] > f[j]) ? f[j - i] + a[i] : f[j];
        }
    }

    // 相减即为最大净收益
    for (int i = 1; i <= 10; i++) {
        f[i] -= v[i];
    }

    // 计算答案
    for (int i = 1; i <= 10; i++) {
        for (int j = i; j <= n; j++) {
            dp[j] = (dp[j - i] + f[i] > dp[j]) ? dp[j - i] + f[i] : dp[j];
        }
    }

    // 找出dp数组中的最大值
    for (int i = 1; i <= n; i++) {
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }

    printf("%lld\n", ans);
    return 0;
}
