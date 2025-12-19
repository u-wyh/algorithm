#include <stdio.h>
#include <string.h>

#define MAXN 101

typedef struct {
    int arr[MAXN];
    int len;
} Number;

Number f[MAXN + 10][MAXN + 10];
int n, val[MAXN][MAXN];

void print(Number x) {
    for (int i = MAXN - x.len; i < MAXN; i++)
        printf("%d", x.arr[i]);
    printf("\n");
}

Number new_number() {
    Number x;
    x.len = 1;
    memset(x.arr, 0, sizeof(x.arr));
    return x;
}

Number number_add(Number x, Number y) {
    int p = 0;
    for (int i = MAXN - 1; i >= MAXN - max(x.len, y.len) || p; i--) {
        x.arr[i] += y.arr[i] + p;
        p = x.arr[i] / 10;
        x.arr[i] %= 10;
        x.len = max(x.len, MAXN - i);
    }
    return x;
}

// 注意：C语言中没有max函数，需要手动实现
int max(int a, int b) {
    return a > b ? a : b;
}

void input() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &val[i][j]);
}

void init() {
    for (int i = 0; i < MAXN + 10; i++)
        for (int j = 0; j < MAXN + 10; j++)
            f[i][j] = new_number();
}

void DP() {
    f[1][1].arr[MAXN - 1] = 1;
    f[1][1].len = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (val[i][j]) {
                f[i + val[i][j]][j] = number_add(f[i + val[i][j]][j], f[i][j]);
                f[i][j + val[i][j]] = number_add(f[i][j + val[i][j]], f[i][j]);
            }
}

void output() {
    print(f[n][n]);
}

int main() {
    input();
    init();
    DP();
    output();
    return 0;
}
