// https://www.luogu.com.cn/problem/P1103
// 题意：给 n 本书的高度和宽度，先按高度从低到高摆好，再拿走恰好 k 本。
// 剩下每对相邻书的宽度差取绝对值并求和，输出能做到的最小和。
// 数据范围：2 ≤ n ≤ 100，1 ≤ k<n，高度、宽度至多 200，
// 所有高度互异。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划、排序

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int n, k, m;
int Min = INT_MAX;
int f[501][501];

int min(int a,int b)
{
    return a<b?a:b;
}

typedef struct {
    int h, w;
} info;

info a[1001];

int cmp(const void *x, const void *y) {
    info *xx = (info *)x;
    info *yy = (info *)y;
    return xx->h - yy->h;
}

int main() {
    scanf("%d %d", &n, &k);
    m = n - k; // 选取m本书
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i].h, &a[i].w);
    }

    qsort(a + 1, n, sizeof(info), cmp); // 高度决定顺序

    memset(f, 0x7f, sizeof(f)); // 初始化为极大值

    for (int i = 1; i <= n; i++) {
        f[i][1] = 0; // 单独选择任何书都不会有花费
    }

    for (int i = 2; i <= n; i++) { // 试着放第i本的时候
        for (int j = 1; j < i; j++) { // 尝试与前面第j本相邻
            for (int l = 2; l <= min(i, m); l++) { // 放下第i本时，长度不超过i和m
                f[i][l] = min(f[i][l], f[j][l - 1] + abs(a[i].w - a[j].w)); // 总花费越小越好
            }
        }
    }

    for (int i = m; i <= n; i++) {
        Min = min(Min, f[i][m]); // 找到以m结尾的最小花费
    }

    printf("%d\n", Min);
    return 0;
}
