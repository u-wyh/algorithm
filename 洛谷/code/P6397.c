// https://www.luogu.com.cn/problem/P6397
// 题意：直线上有 n 个信使按坐标不降序排列，初始 1 号得知消息。
// 任意时刻每个信使可向左/右以速度 1 移动或不动，距离不超过 k 时可瞬间传递消息，求所有信使都得知消息的最短时间（误差不超过 10^-3）。
// 数据范围：1 <= n <= 10^5，0 <= k <= 10^6，0 <= d_i <= 10^9（实数，小数点后 3 位）。
// 算法标签：二分答案、贪心
#include <stdio.h>
#define ll long long

double d[100005];
double k;
int n;

int check(double x) {
    double maxx = d[1] + x; // 1号信使极限最右位置
    for (int i = 2; i <= n; i++) {
        if (d[i] - x - maxx > k) return 0; // 若i号信使向左靠拢都不行，则无法满足条件
        maxx += k; // 若可以则使i号信使走到距离i-1号信使k的位置
        if (d[i] + x < maxx) maxx = d[i] + x; // 如果用尽时间都走不到，则更新maxx为i号信使的极限位置
    }
    return 1;
}

int main() {
    scanf("%lf%d", &k, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &d[i]);
    double l = 0, r = d[n], ans = 0;
    while (r - l >= 0.000001) {
        double mid = (l + r) / 2.0;
        if (check(mid)) {
            ans = mid;
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.3lf\n", ans);
    return 0;
}
