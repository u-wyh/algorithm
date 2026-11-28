// https://www.luogu.com.cn/problem/P2064
// 题意：从第 1 天行驶任意正整数距离 a 出发，
// 每天路程须为前一天的 2~9 的整数倍。
// 要求至少行驶 2 天，且总路程恰好等于给定的正整数 S。
// 输出最少行驶天数；若无解输出 -1。
// 数据范围：
// 9 < S <= 10^8（总里程）
// 难度评分：1400（洛谷分级换算）
// 算法标签：深度优先搜索、数论
#include <stdio.h>
#include <math.h>

#define INF 0x7fffffff

int n, ans = INF;

// 声明深度优先搜索函数
void dfs(int dep, int num);

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= (int)sqrt(n); i++) {
        // 因数一定是成对出现，所以我们枚举的a实际上是i和n/i
        if (n % i == 0) {
            if (n / i != i) dfs(0, i);  // n/(n/i)=i
            if (i != 1 && i != n) dfs(0, n / i);  // 避免重复和n本身的情况
        }
    }
    if (ans != INF) printf("%d\n", ans);  // 判断能否到达
    else printf("-1\n");
    return 0;
}

// 定义深度优先搜索函数
void dfs(int dep, int num) {
    if (num == 0) {
        // 边界条件
        if (dep < ans) ans = dep;  // 更新最小深度
        return;
    }
    num--;  // 把式子里面的1减掉
    for (int i = 2; i <= 9; i++) {  // 枚举k
        if (num % i == 0) {  // 判断整除
            dfs(dep + 1, num / i);
        }
    }
}
