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