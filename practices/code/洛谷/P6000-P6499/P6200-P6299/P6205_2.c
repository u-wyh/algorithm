// https://www.luogu.com.cn/problem/P6205
// 题意：商场有价格为 1, 2, ..., K 元的 K 种工具（每种无限），
// 手里有 N 元必须恰好花完，求不同的无序购买方案数（需高精度）。
// 数据范围：1 <= K <= 100，1 <= N <= 1000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：完全背包、动态规划
#include <stdio.h>
#include <string.h>

#define rei int
#define FOR(i, l, r) for(rei i = l; i <= r; ++i)

typedef __int128 ll;

ll f[1001];
int n, m;

void print(ll x) { // 快写
    if (x == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    char buf[50]; // 假设数字不会超过49位（实际上__int128的十进制表示可能更长，但这里为了简化）
    int pos = 0;
    while (x > 0) {
        buf[pos++] = (x % 10) + '0';
        x /= 10;
    }
    for (int i = pos - 1; i >= 0; --i) {
        putchar(buf[i]);
    }
    putchar('\n');
}

int main() {
    scanf("%d%d", &m, &n);
    memset(f, 0, sizeof(f)); // 初始化f数组为0
    f[0] = 1;
    FOR(i, 1, n) // 外层循环枚举物品，内层循环枚举钱数
        FOR(j, i, m)
            f[j] += f[j - i];
    print(f[m]);
    return 0;
}
