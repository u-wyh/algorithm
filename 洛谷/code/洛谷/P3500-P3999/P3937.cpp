// https://www.luogu.com.cn/problem/P3937
// 题意：n 盏灯环形排列（标号 1..n），
// 给定时刻 0 时每盏灯的状态 a_i in {0, 1}。
// 每个时刻到下一时刻，
// 每盏灯的状态变为它与顺时针方向下一盏灯当前状态的异或（相同为 0，不同为 1）。
// 求时刻 t 第 k 盏灯的状态。
// 数据范围：1 <= t, k <= n <= 3 * 10^6。
// 算法标签：卢卡斯定理、位运算
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, t, k;
    cin >> n >> t >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int pos = k - 1; // 转换为0-based索引
    int ans = 0;
    
    // 枚举t的所有子集（包括0）
    for (int s = t; ; s = (s - 1) & t) {
        int idx = (pos + s) % n; // 环形下标处理
        ans ^= a[idx];          // 异或累积
        if (s == 0) break;      // 处理完所有子集后退出
    }
    
    cout << ans << endl;
    return 0;
}