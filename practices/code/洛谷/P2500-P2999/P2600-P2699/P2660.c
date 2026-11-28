// https://www.luogu.com.cn/problem/P2660
// 题意：在 x*y 的矩形田地上每次种一个正方形（不能重复种），
// 花费体力为正方形周长。
// 求种完整个矩形的最小体力总和。
// 输出最小体力总和。
// 数据范围：1 <= x, y <= 10^16。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、辗转相除法
#include <stdio.h>

int main() {
    long long x, y, ans = 0, temp;
    scanf("%lld %lld", &x, &y);

    while (x && y) { // 如果x和y都不为0，则继续循环
        // 交换x和y的值
        temp = x;
        x = y;
        y = temp;

        // 计算并累加当前可种植的最大正方形数量
        ans += 4 * y * (x / y);

        // 更新x的值为x除以y的余数
        x %= y;
    }

    // 输出结果
    printf("%lld\n", ans);

    return 0;
}
