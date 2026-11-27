// https://www.luogu.com.cn/problem/P3606
// 题意：输入谷仓层数 N、奶牛总数 K，以及每层楼的工作量 a_1..a_N。
// 将 K 头奶牛全部分配到 N 层楼，每层至少分配 1 头牛；
// 若有 c 头牛在第 i 层工作，则该层耗时为 a_i / c，且各层须依次建造。
// 输出完成全部 N
// 层所需的最小总时间四舍五入后的整数（保证答案距半整数至少 0.1）。
// 数据范围：1 <= N <= K <= 10^12，N <= 10^5，
// 1 <= a_i <= 10^12（正整数）。
// 算法标签：二分答案、数学、贪心
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
long long m;
long long a[MAXN];

bool check(double k) {
    long long total = 0;
    for (int i = 1; i <= n; i++) {
        double x = (sqrt(1 + 4.0 * a[i] / k) - 1) / 2.0;
        long long v = ceil(x);
        total += v;
        if (total > m) return false;
    }
    return true;
}

int main() {
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    double l = 1e-18; // 避免除0
    double r = 1e18;  // 覆盖极大值
    double ans = r;   // 初始化

    // 固定100次二分迭代确保精度
    for (int iter = 0; iter < 100; iter++) {
        double mid = (l + r) * 0.5;
        if (check(mid)) {
            ans = mid;
            r = mid;
        } else {
            l = mid;
        }
    }

    long long total_v = 0;
    double total_cost = 0.0;
    for (int i = 1; i <= n; i++) {
        double x = (sqrt(1 + 4.0 * a[i] / ans) - 1) / 2.0;
        long long v = ceil(x);
        total_v += v;
        total_cost += static_cast<double>(a[i]) / v;
    }

    double final_ans = total_cost - (m - total_v) * ans;
    printf("%.0lf\n", final_ans);
    return 0;
}