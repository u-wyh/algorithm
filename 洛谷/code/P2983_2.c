// https://www.luogu.com.cn/problem/P2983
// 题意：输入巧克力种类数 N、总预算 B，以及每种巧克力的单价 P_i 和只喜欢该种巧克力的奶牛数量 C_i（每种巧克力供应无限）。
// 每头牛只对其指定的唯一一种巧克力感到满意；在总花费不超过预算 B 的前提下购买巧克力分配给奶牛。
// 求最多能满足多少头奶牛。
// 输出一行一个整数，表示最多能满足的奶牛数量。
// 数据范围：对于 100% 的数据，1 <= N <= 100000，1 <= P_i <= 10^18，1 <= C_i <= 10^18
// 1 <= B <= 10^18。
#include <stdio.h>
#include <stdlib.h>
// 算法标签：贪心、排序

typedef struct {
    long long int p, c; // p代表该巧克力价格，c表示喜欢该巧克力的奶牛数
} cow;

cow c[100002];

// 比较函数，用于qsort
int com(const void *a, const void *b) {
    cow *ca = (cow *)a;
    cow *cb = (cow *)b;
    if (ca->p < cb->p) return -1;
    if (ca->p > cb->p) return 1;
    return 0;
}

int main() {
    int n;
    unsigned long long int b, ans = 0; // 预算和答案
    scanf("%d %llu", &n, &b); // 读取n和b

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &c[i].p, &c[i].c); // 读取价格和喜欢该巧克力的奶牛数
    }

    // 使用qsort进行排序
    qsort(c, n, sizeof(cow), com);

    for (int i = 0; i < n; i++) {
        if (b > c[i].c * c[i].p) {
            // 如果预算足够购买当前巧克力
            ans += c[i].c;
            b -= c[i].c * c[i].p;
        } else {
            // 如果预算不足，尽量多地购买
            ans += b / c[i].p;
            break; // 跳出循环，因为后续巧克力更贵
        }
    }

    printf("%llu\n", ans);
    return 0;
}
