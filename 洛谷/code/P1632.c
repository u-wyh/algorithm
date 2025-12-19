#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y;
} coord;

coord a[55];
int n, ans[55], dis[55];

int compareInts(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    memset(ans, 0x3f, sizeof(ans)); // 初始化为一个大数
    for (int i = 0; i < n; i++) { // 注意数组索引从0开始
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            for (int p = 0; p < n; p++) {
                dis[p] = abs(a[p].x - a[x].x) + abs(a[p].y - a[y].y);
            }
            qsort(dis, n, sizeof(int), compareInts);
            for (int p = 0; p < n; p++) {
                if (p > 0) {
                    dis[p] += dis[p - 1];
                }
                ans[p] = (ans[p] < dis[p]) ? ans[p] : dis[p]; // 使用三元运算符进行最小值比较
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
