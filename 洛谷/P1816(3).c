#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} fff;

fff a[100001];

// 比较函数，用于qsort
int cmp(const void *l, const void *v) {
    fff *left = (fff *)l;
    fff *right = (fff *)v;
    return left->x - right->x;
}

int main() {
    int m, n, t, k;
    scanf("%d%d", &m, &n);

    for (int i = 0; i < m; i++) {  // 注意数组索引从0开始
        scanf("%d", &a[i].x);
        a[i].y = i + 1;  // 为每个账目编号，从1开始
    }

    qsort(a, m, sizeof(fff), cmp);  // 使用qsort进行排序

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &t, &k);
        int found = 0;  // 标记是否找到
        for (int j = 0; j < m; j++) {
            if (a[j].y >= t && a[j].y <= k) {
                printf("%d ", a[j].x);
                found = 1;
                break;  // 一个小优化
            }
        }
        if (!found) {  // 如果没有找到，则输出一个特殊值或不做任何操作（这里未做处理）
            // 可以选择添加一些输出，比如"Not Found"
        }
    }

    return 0;
}
