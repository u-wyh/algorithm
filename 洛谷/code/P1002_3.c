// https://www.luogu.com.cn/problem/P1002
// 题意：卒从 (0, 0) 出发，每步只能向下或向右，目标是 (n, m)。
// 给出一匹位置固定的马。卒要避开马所在的格子和马一步能跳到的格子。
// 输出到达目标的走法数，保证起点安全。
// 数据范围：1 ≤ n, m ≤ 20，马的两个坐标均在 [0, 20]。
// 算法标签：动态规划、滚动数组

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define ll long long

int read() {
    int num = 0;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) {
        num = (num << 1) + (num << 3) + (c ^ '0');
        c = getchar();
    }
    return num;
}

int bx, by, mx, my;
ll f[30];

int abs(int x) {
    return x < 0 ? -x : x;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int check(int x, int y) {
    if (x == mx && y == my) return 1;
    return (abs(mx - x) + abs(my - y) == 3) && (max(abs(mx - x), abs(my - y)) == 2);
}

int main() {
    bx = read() + 2;
    by = read() + 2;
    mx = read() + 2;
    my = read() + 2;
    f[2] = 1;
    for (int i = 2; i <= bx; i++) {
        for (int j = 2; j <= by; j++) {
            if (check(i, j)) {
                f[j] = 0;
                continue;
            }
            f[j] += f[j - 1];
        }
    }
    printf("%lld\n", f[by]);
    return 0;
}
