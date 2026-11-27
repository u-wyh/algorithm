// https://www.luogu.com.cn/problem/P10460
// 题意：每组给 N 个等差序列，参数 (S,E,D) 表示从 S 起每次加 D，
// 保留不超过 E 的项。
// 保证最多只有一个位置出现奇数次。
// 若有就输出该位置和出现次数，否则输出 There's no weakness.。
// 数据范围：1 ≤ T ≤ 5，N ≤ 2 × 10^5，S ≤ E，
// 三个参数均在 [0,2^31-1]，序列总项数不超过 10^8。
// 算法标签：枚举、异或

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
