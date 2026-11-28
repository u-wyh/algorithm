// https://www.luogu.com.cn/problem/P2887
// 题意：输入奶牛数 C、防晒霜种类数 L，
// 每头牛可接受的阳光强度范围 [minSPF[i], maxSPF[i]]
// 以及每种防晒霜的固定强度 SPF[i] 和瓶数 cover[i]。
// 每头牛最多涂一瓶防晒霜，涂后接收到的阳光强度稳定为 SPF[i]，
// 须落在该牛的区间内才能满足该牛。
// 合理分配防晒霜，最大化能够满足的奶牛数量。
// 输出一个整数，表示最多能满足日光浴的奶牛数目。
// 数据范围：对于 100% 的数据，1 <= C, L <= 2500，
// 1 <= minSPF[i] <= maxSPF[i] <= 1000
// 1 <= SPF[i] <= 1000，
// 1 <= cover[i] <= 2500。
// 难度评分：1200（洛谷分级换算）
// 算法标签：贪心、排序
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
} node;

node cow[2501], fss[2501];
int c, l, ans;

// 自定义比较函数，用于qsort
int cmp(const void *a, const void *b) {
    node *x = (node *)a;
    node *y = (node *)b;
    return x->b - y->b; // 奶牛按右端点排序
}

int cmp1(const void *a, const void *b) {
    node *x = (node *)a;
    node *y = (node *)b;
    return x->a - y->a; // 防晒霜按左端点排序
}

int main() {
    scanf("%d%d", &c, &l);
    for (int i = 0; i < c; i++) {
        scanf("%d%d", &cow[i].a, &cow[i].b);
    }
    for (int i = 0; i < l; i++) {
        scanf("%d%d", &fss[i].a, &fss[i].b);
    }

    // 使用qsort进行排序
    qsort(cow, c, sizeof(node), cmp);
    qsort(fss, l, sizeof(node), cmp1);

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < l; j++) {
            if (fss[j].b > 0 && fss[j].a >= cow[i].a && fss[j].a <= cow[i].b) {
                fss[j].b--;
                ans++;
                break;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
