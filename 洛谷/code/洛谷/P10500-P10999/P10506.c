// https://www.luogu.com.cn/problem/P10506
// 题意：给 n 堆珠子，两人轮流选一堆数量 p 大于 1 的珠子，
// 把它换成大小各为 p 的一个真约数的若干堆，再删去其中一堆。
// 无法行动者输，双方最优时输出先手 freda 或后手 rainbow。
// 数据范围：多组数据读到 EOF，1 ≤ n ≤ 100，
// 1 ≤ a[i] ≤ 1000。
// 算法标签：SG函数、记忆化搜索

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int sg[1001], a[1001];

int SG(int m) {
    if (sg[m] != -1)
        return sg[m];

    int k = 0;
    for (int i = 1; i * i <= m; ++i)
        if (m % i == 0) {
            if (i < m)
                k ^= SG(i);
            if (m / i > 1 && m / i < m && i * i != m)
                k ^= SG(m / i);
        }

    bool flag[1001];
    memset(flag, 0, sizeof(flag));
    for (int i = 1; i * i <= m; ++i)
        if (m % i == 0) {
            if (i < m)
                flag[k ^ sg[i]] = true;
            if (m / i > 1 && m / i < m && i * i != m)
                flag[k ^ sg[m / i]] = true;
        }

    int t = 0;
    while (flag[t])
        t++;
    return sg[m] = t;
}

void work(int n) {
    memset(sg, -1, sizeof(sg));
    sg[1] = 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        ans ^= SG(a[i]);
    }
    if (ans != 0)
        printf("freda\n");
    else
        printf("rainbow\n");
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF)
        work(n);
    return 0;
}
