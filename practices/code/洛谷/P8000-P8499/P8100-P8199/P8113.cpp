// https://www.luogu.com.cn/problem/P8113
// 题意：n 位居民依次给平台评分，平台最高分为 m，初始平台平均分为 0。
// 第 i 位居民心理预期分数为 a_i：当他评分时，
// 若当前平台平均分严格高于 a_i，则打 0 分；
// 否则（<= a_i）打 m 分。
// 求所有居民在不同排列顺序下评分，最终平台平均分可能的最大值与最小值。
// 第一行输入 n, m，第二行 n 个整数 a_i。
// 输出一行两个实数，保留 2 位小数。
// 数据范围：1 < n, m <= 10^5，a_i ∈ [0, m]∩Z。
// 算法标签：贪心、排序
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