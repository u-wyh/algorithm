// https://www.luogu.com.cn/problem/P10377
// 题意：从一排牛棚中保留连续一段，安排 n 头牛各占一间。第 i 头牛左侧 a[i] 间和右侧 b[i] 间内都不能有其他牛。
// 求至少要保留多少间才有可行安排。
// 数据范围：共有 10^9 间牛棚，1 ≤ n ≤ 9，1 ≤ a[i],b[i] ≤ 1000。
// 算法标签：排列枚举、回溯

#include <stdio.h>
#include <limits.h>

typedef struct {
    int a, b;
} Cow;

Cow cows[10];
int n, minn = INT_MAX;
int bj[10];
int fzsx[10];

void add() {
    int sum = 1;  // 第一头牛需要一个牛棚
    for (int i = 2; i <= n; i++) {
        sum += (cows[fzsx[i]].b > cows[fzsx[i - 1]].a) ? cows[fzsx[i]].b : cows[fzsx[i - 1]].a;
        sum += 1;  // 加上当前牛的牛棚
    }
    if (sum < minn) {
        minn = sum;
    }
}

void dfs(int x) {
    if (x - 1 == n) {
        add();
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!bj[i]) {
            bj[i] = 1;
            fzsx[x] = i;
            dfs(x + 1);
            bj[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cows[i].a);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cows[i].b);
    }
    dfs(1);
    printf("%d\n", minn);
    return 0;
}
