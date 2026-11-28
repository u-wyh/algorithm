// https://www.luogu.com.cn/problem/P1455
// 题意：给 n 件商品的价格和价值，并给一些必须搭配购买的双向关系。
// 选一件就要同时买下跟它直接或间接搭配的所有商品。
// 求总价不超过预算 w 时的最大总价值。
// 数据范围：1 ≤ n,w,c[i],d[i] ≤ 10000，
// 0 ≤ m ≤ 5000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集、背包动态规划

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // 用于isalnum

int read() // 快读
{
    int num = 0, f = 1;
    char ch = getchar();

    while (!isalnum(ch)) {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (isalnum(ch)) {
        num = num * 10 + (ch - '0');
        ch = getchar();
    }
    return num * f;
}

int father[10001]; // 并查集数组

int find(int x) // 并查集函数
{
    if (father[x] == x) {
        return x;
    }
    return father[x] = find(father[x]);
}

int c[10001], d[10001], f[100001]; // DP数组，注意f数组的大小可能需要调整以支持更大的w

int main()
{
    int n = read(), m = read(), w = read();
    for (int i = 1; i <= n; i++) { // 初始化并查集
        father[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        c[i] = read();
        d[i] = read();
    }

    int x, y;
    for (int i = 1; i <= m; i++) { // 并查集
        x = read();
        y = read();
        father[find(x)] = find(y);
    }

    for (int i = 1; i <= n; i++) { // 将同集合的云朵的价钱与价值都划到一个云朵里
        if (father[i] != i) {
            d[find(i)] += d[i];
            d[i] = 0;
            c[find(i)] += c[i];
            c[i] = 0;
        }
    }

    for (int i = 1; i <= n; i++) { // DP
        for (int v = w; v >= c[i]; v--) {
            f[v] = (f[v] > f[v - c[i]] + d[i]) ? f[v] : (f[v - c[i]] + d[i]);
        }
    }
    printf("%d\n", f[w]);
    return 0;
}
