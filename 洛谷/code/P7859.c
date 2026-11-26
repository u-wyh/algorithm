// https://www.luogu.com.cn/problem/P7859
// 题意：有 N 种原材料（编号 1..N）和 M 对冲突关系 (x_i, y_i)。
// 选出一个原材料子集（可以为空集），要求其中不能同时包含任意一对冲突的原材料。
// 第一行输入 N, M，接下来 M 行每行 x_i, y_i。
// 输出一行一个整数表示合法方案数。
// 数据范围：1 <= N <= 20，0 <= M <= 400，1 <= x_i, y_i <= N，x_i != y_i。
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x, y;
} node;

node b[405];
int n, m, a[405], ans;

int main() {
    scanf("%d %d", &n, &m);
    int x, y;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &b[i].x, &b[i].y);
    }

    for (int i = 0; i < (1 << n); i++) {
        bool bj = false; // C语言中，布尔类型用false和true表示
        for (int j = 1; j <= m; j++) {
            if ((i & (1 << (b[j].x - 1))) && (i & (1 << (b[j].y - 1)))) {
                bj = true;
                break;
            }
        }
        if (!bj) ans++;
    }

    printf("%d\n", ans);
    return 0;
}
