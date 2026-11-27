// https://www.luogu.com.cn/problem/P1083
// 题意：第 i 天有 r[i] 间教室。
// 按输入顺序接订单，订单 (d,s,t) 要求从 s 到 t 的每一天都给 d 间。
// 找到第一份有一天教室不够的订单，有则先输出 -1 再输出订单编号，全能满足就输出 0。
// 数据范围：1 ≤ n,m ≤ 10^6，0 ≤ r[i],d ≤ 10^9，1 ≤ s ≤ t ≤ n。
// 算法标签：二分答案、差分、前缀和

#include <stdio.h>
#include <string.h>

int n, m;
long long  diff[1000011], need[1000011], rest[1000011], r[1000011], l[1000011], d[1000011];

int isok(int x) {
    memset(diff, 0, sizeof(diff));
    for (int i = 1; i <= x; i++) {
        diff[l[i]] += d[i];
        if (r[i] + 1 <= n) {
            diff[r[i] + 1] -= d[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        need[i] = need[i - 1] + diff[i];
        if (need[i] > rest[i]) return 0;
    }
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &rest[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lld%lld%lld", &d[i], &l[i], &r[i]);
    }
    int begin = 1, end = m;
    if (isok(m)) {
        printf("0\n");
        return 0;
    }
    while (begin < end) {
        int mid = (begin + end) / 2;
        if (isok(mid)) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    printf("-1\n%d\n", begin);
    return 0;
}
