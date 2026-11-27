// https://www.luogu.com.cn/problem/P6183
// 题意：有 n 个初始全空的洞（用 O 表示空、X 表示盖住），
// 每次翻动一个洞的状态；
// 要求构造共 2^n + 1 行的操作序列，
// 从全 O 出发遍历所有 2^n 种状态各一次后回到全 O。
// 数据范围：1 <= n <= 15。
// 算法标签：格雷码、构造
#include <stdio.h>

#define MAX_N 70000
#define MAX_COLUMNS 20

int n, mapp[MAX_N][MAX_COLUMNS], num = 2;

int main() {
    mapp[1][1] = 0;  // 储存 n=1 时的答案。
    mapp[2][1] = 1;

    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {  // 由于每一个 i 都要用到 i-1 时的答案
        num *= 2;  // 所以需要算出 2 到 n 的所有答案

        // 翻转上半部分到下半部分
        for (int j = 1; j <= num / 2; j++) {
            for (int k = 1; k < i; k++) {
                mapp[num / 2 + j][k] = mapp[num / 2 - j + 1][k];
            }
        }

        // 设定后半部分末尾为 1，前半部分末尾为 0
        for (int j = 1; j <= num; j++) {
            if (j > num / 2) {
                mapp[j][i] = 1;
            } else {
                mapp[j][i] = 0;
            }
        }
    }

    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= n; j++) {
            if (mapp[i][j]) {
                printf("X");  // 别忘记转换成 O 和 X。
            } else {
                printf("O");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        printf("O");
    }
    printf("\n");

    return 0;
}
