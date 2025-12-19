#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 升序排序（求最大平均分）
    vector<int> b = a;
    sort(b.begin(), b.end());
    long long total_max = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (total_max > 1LL * b[i] * cnt) {
            cnt++;
        } else {
            total_max += m;
            cnt++;
        }
    }

    // 降序排序（求最小平均分）
    sort(b.rbegin(), b.rend());
    long long total_min = 0;
    cnt = 0;
    for (int i = 0; i < n; i++) {
        if (total_min > 1LL * b[i] * cnt) {
            cnt++;
        } else {
            total_min += m;
            cnt++;
        }
    }

    // 计算并输出结果
    double avg_max = static_cast<double>(total_max) / n;
    double avg_min = static_cast<double>(total_min) / n;
    printf("%.2lf %.2lf\n", avg_max, avg_min);
    
    return 0;
}