#include <stdio.h>
#include <stdlib.h>

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
