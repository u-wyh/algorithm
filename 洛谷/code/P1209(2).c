#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int a[201], b[201];
    int n, m, s, long1, ans, i;

    scanf("%d %d %d", &n, &m, &s); // 读取n, m, s

    for (i = 1; i <= s; i++) {
        scanf("%d", &a[i]); // 读取码头位置
    }

    qsort(a + 1, s, sizeof(int), compare); // 对码头位置进行排序

    for (i = 2; i <= s; i++) {
        b[i] = a[i] - a[i - 1] - 1; // 计算相邻码头之间的距离
    }

    qsort(b + 2, s - 1, sizeof(int), compare); // 对距离进行排序

    ans = s; // 默认每个码头都需要一块木板
    long1 = s; // 默认总长度为s（假设每块木板长度为1）

    for (i = 2; ans > n; i++) { // 当木板数量超过n时
        ans--; // 木板数量减一
        long1 += b[i]; // 将当前最大的间隔加到总长度上
    }

    printf("%d\n", long1); // 输出总长度

    return 0;
}
