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