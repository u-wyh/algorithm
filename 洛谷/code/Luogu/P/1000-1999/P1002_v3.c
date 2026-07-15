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
