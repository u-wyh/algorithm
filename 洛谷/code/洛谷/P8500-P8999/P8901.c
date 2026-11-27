// https://www.luogu.com.cn/problem/P8901
// 题意：T 组数据，环形牛棚有 N 个房间（房间 N 连向房间 1），
// 第 i 个房间初始有 a_i 头牛。
// 两人轮流行动，FJ 先手，初始都在房间 1。
// 轮到某人时若当前房间牛数为 0 则判负；
// 否则其可移走 P 头牛（P=1 或不超过当前牛数的质数），
// 两人各行动一次后一起移动到下一房间。
// 双方最优策略下输出获胜者（Farmer John 或 Farmer Nhoj）。
// 数据范围：1 <= T <= 1000，
// 1 <= N <= 10^5，sum N <= 2*10^5，
// 1 <= a_i <= 5*10^6。
// 算法标签：线性筛、博弈论
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define N 100010
#define M 5000010

int T, n, x, cnt, ans, mx[4], v[M+10], vis[M+10], prime[M];

void get_prime(int n) {
    vis[1] = 1;
    mx[1] = 1;
    v[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            mx[i % 4] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = 1;
            if (!(i % prime[j])) {
                break;
            }
        }
        v[i] = !(i % 4) ? i / 2 : (i - mx[i % 4]) / 2 + 1;
    }
}

int main() {
    scanf("%d", &T);
    get_prime(M);
    while (T--) {
        scanf("%d", &n);
        ans = INT_MAX;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            if (v[x] / 2 < ans / 2)
                ans = v[x];
        }
        if (ans & 1) {
            printf("Farmer John\n");
        } else {
            printf("Farmer Nhoj\n");
        }
    }
    return 0;
}
