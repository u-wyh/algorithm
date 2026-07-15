#include <stdio.h>

#define MAX_N 152  // 因为数组索引从0开始，所以定义为152以支持0到151的索引

int main() {
    int a[MAX_N], b[MAX_N];  // 起始和结束时间数组
    int n, i, j, t, t1, s;

    scanf("%d", &n);  // 读取节目数量
    for (i = 0; i < n; i++) {
        scanf("%d %d", &a[i], &b[i]);  // 读取每个节目的开始和结束时间
    }

    // 按结束时间排序，如果结束时间相同，则按开始时间排序
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (b[i] > b[j] || (b[i] == b[j] && a[i] > a[j])) {
                t = b[i];
                b[i] = b[j];
                b[j] = t;
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

    t = 0;
    t1 = 0;  // 两组的结束时间
    s = 0;   // 节目数量

    for (i = 0; i < n; i++) {
        if (a[i] >= t) {  // 能放在第1组
            s++;
            if (t1 >= t && a[i] >= t1) {
                t1 = b[i];  // 第2组能放且更优
            } else {
                t = b[i];
            }
        } else if (a[i] >= t1) {  // 能放在第2组
            s++;
            t1 = b[i];
        }
    }

    printf("%d\n", s);  // 输出能安排的节目数量
    return 0;
}
