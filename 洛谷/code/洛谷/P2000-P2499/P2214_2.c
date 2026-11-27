// https://www.luogu.com.cn/problem/P2214
// 题意：N 个牧场排成一排，B 种奶牛叫声音量 V_i。
// 每个牧场总音量 = 本牧场奶牛音量 + max(0, 前一牧场总音量 - 1)。
// 已知各牧场总音量，求最少奶牛数量，无解输出 -1。
// 数据范围：1 <= N <= 100，1 <= B <= 20，
// 1 <= V_i <= 100，每牧场奶牛总音量 <= 10^5。
// 算法标签：完全背包、差分
#include <stdio.h>
#include <limits.h>

#define N 100005
#define INF 1000000000

int f[N + 5], v[N + 5], n, b, u, now, ans;

// 实现min函数
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &n, &b);
    for (int i = 0; i <= N; i++) {
        f[i] = INF;
    }
    f[0] = 0;

    for (int i = 1; i <= b; i++) {
        scanf("%d", &v[i]);
        for (int j = v[i]; j <= N; j++) {
            f[j] = min(f[j], f[j - v[i]] + 1);
        }
    }

    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        x -= now;
        now += x;
        // 如果now为0，则不减少步数
        if (now > 0) {
            now--;
        }
        if (x < 0) {
            printf("-1");
            return 0;
        }
        if (f[x] == INF) {
            printf("-1");
            return 0;
        }
        ans += f[x];
    }

    printf("%d", ans);
    return 0;
}
