// https://www.luogu.com.cn/problem/P1290
// 题意：给定正整数 M 和 N，Stan 先手与 Ollie 轮流从较大数中减去较小数的正整数倍（结果 >= 0）。
// 题意：先使其中一个数变为 0 者获胜，双方均采用最优策略，判断每组胜者。
// 输入：第一行输入数据组数 C，接下来 C 行每行输入两个正整数 M, N。
// 输出：每组输出一行，Stan wins 或 Ollie wins。
// 数据范围：1 <= C <= 6。
// 数据范围：1 <= M, N < 2^31。
#include <stdio.h>
// 算法标签：博弈论、递归

int m, n, q;

// 当前操作者为p, p为0时代表Stan操作, p为1时代表Ollie操作。
int find(int x, int y, int p) {
    if (x == y) return p; // 返回胜者
    if (y / x >= 2) return p; // 返回胜者
    else return find(y - x, x, p ^ 1); // 向下一个状态查找
}

int main() {
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &m, &n);
        if (m > n) {
            int temp = m;
            m = n;
            n = temp;
        }
        if (find(m, n, 0) == 0) {
            printf("Stan wins\n"); // 如果返回0, 胜者为Stan
        } else {
            printf("Ollie wins\n"); // 反之则为Ollie
        }
    }
    return 0;
}
