// https://www.luogu.com.cn/problem/P8311
// 题意：有 n 个点，
// 在点 a 和点 b 之间修路的长度（代价）为 d_a + d_b，
// 求使所有点连通所需的最小总道路长度（n=1 时为 0）。
// 数据范围：100% 数据满足 1 <= n <= 10^5，
// 1 <= d_i <= 10^9。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、数学
#include <stdio.h>
#include <limits.h> // 用于INT_MAX或自定义大数，但这里直接用了一个大数

#define ll long long

int main() {
    ll a, b, ans = 0, min = 1000000005; // 不开long long见祖宗（这句是玩笑话，但确实需要注意数据范围）

    // 使用scanf读取a
    scanf("%lld", &a);

    // 特判a是否为1
    if (a == 1) {
        printf("0\n"); // 注意C语言printf不会自动换行，需要手动添加\n
    } else {
        for (int i = 1; i <= a; i++) {
            // 使用scanf读取b
            scanf("%lld", &b);
            // 累加总和
            ans += b;
            // 更新最小值
            if (b <= min) {
                min = b;
            }
        }
        // 计算并输出结果
        // 注意：这里假设a不会为0（已在特判中处理），所以可以直接进行运算
        printf("%lld\n", a * min - min * 2 + ans);
    }

    return 0;
}
