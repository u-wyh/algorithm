#include <stdio.h>

typedef struct {
    int st;
    int en;
    int dis;
} defender;

defender arr[200005];

int main() {
    int t, n, s, e, d;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) { // 注意C语言中数组索引从0开始
        scanf("%d", &n);
        int m = 0;
        for (int j = 0; j < n; j++) { // 同样注意索引
            scanf("%d%d%d", &s, &e, &d);
            arr[j].st = s;
            arr[j].en = e;
            arr[j].dis = d;
            for (int k = s; k <= e; k += d) {
                m ^= k; // 使用异或运算来“标记”存在的数字
            }
        }
        if (m == 0) {
            printf("There's no weakness.\n");
            continue;
        }
        int num = 0;
        for (int j = 0; j < n; j++) { // 检查m是否在某个区间的d的倍数上
            if (m <= arr[j].en && m >= arr[j].st && (m - arr[j].st) % arr[j].dis == 0) {
                num++;
            }
        }
        printf("%d %d\n", m, num);
    }
    return 0;
}
