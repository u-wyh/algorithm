#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int inv2 = 499122177;   // 2的逆元
const int inv6 = 166374059;   // 6的逆元

struct Node {
    int f, g, h;
};

Node compute(int n, int a, int b, int c) {
    if (n < 0) {
        return {0, 0, 0};
    }
    
    if (a >= c || b >= c) {
        // 提取整数部分时的转换
        int a1 = a / c, a2 = a % c;
        int b1 = b / c, b2 = b % c;
        Node t = compute(n, a2, b2, c);
        
        int n1 = n % MOD, n2 = (n + 1) % MOD;
        int n3 = (2 * n + 1) % MOD;
        
        int f = (t.f + a1 * n1 % MOD * n2 % MOD * inv2 % MOD + b1 * n2 % MOD) % MOD;
        
        int g = t.g;
        g = (g + 2 * a1 % MOD * t.h % MOD) % MOD;
        g = (g + 2 * b1 % MOD * t.f % MOD) % MOD;
        g = (g + a1 * a1 % MOD * n1 % MOD * n2 % MOD * n3 % MOD * inv6 % MOD) % MOD;
        g = (g + b1 * b1 % MOD * n2 % MOD) % MOD;
        g = (g + a1 * b1 % MOD * n1 % MOD * n2 % MOD) % MOD;
        
        int h = t.h;
        h = (h + a1 * n1 % MOD * n2 % MOD * n3 % MOD * inv6 % MOD) % MOD;
        h = (h + b1 * n1 % MOD * n2 % MOD * inv2 % MOD) % MOD;
        
        return {f, g, h};
    }
    else{
        // 交换参数时的转换
        int m = (a * n + b) / c;
        Node t = compute(m - 1, c, c - b - 1, a);
        
        int f = ((n*m)% MOD - t.f + MOD) % MOD;
        int g = ((n*m)% MOD * ((m + 1) % MOD) % MOD - 2 * t.h - 2 * t.f - f) % MOD;
        g = (g % MOD + MOD) % MOD;
        int h = (n * (n + 1) % MOD * (m % MOD) % MOD - t.g - t.f) % MOD * inv2 % MOD;
        h = (h % MOD + MOD) % MOD;
        
        return {f, g, h};
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, a, b, c;
        cin >> n >> a >> b >> c;
        
        Node ans = compute(n, a, b, c);
        ans.f = (ans.f % MOD + MOD) % MOD;
        ans.g = (ans.g % MOD + MOD) % MOD;
        ans.h = (ans.h % MOD + MOD) % MOD;
        
        cout << ans.f << " " << ans.g << " " << ans.h << "\n";
    }
    
    return 0;
}