// 连续阶乘逆元的线性递推
// 实现组合公式C(n,m)的计算
// 最终结果 % 1000000007后返回
// 0 <= m <= n <= 1000
// 对数器验证
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int LIMIT = 1000;

// 阶乘表
// fac[i] 代表 i! 在 %MOD 意义下的余数
long long fac[LIMIT + 1];

// 阶乘结果的逆元表
// inv[i] 代表 i! 在 %MOD 意义下的逆元 (1 / i!)
long long inv[LIMIT + 1];

// 快速幂函数，计算 x^n % MOD
long long power(long long x, int n) {
    long long ans = 1;
    while (n > 0) {
        if (n & 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ans;
}

// 初始化阶乘表和逆元表
void build() {
    //先求出阶乘表
    fac[0] = 1; // 0! = 1
    for (int i = 1; i <= LIMIT; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }

    // 利用线性递推优化计算逆元
    inv[LIMIT] = power(fac[LIMIT], MOD - 2);//求出最后一个数字的阶乘逆元
    for (int i = LIMIT - 1; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;//线性递推
    }
}

// 组合公式 C(n, m) % MOD
// 使用阶乘表和逆元表
int c2(int n, int m) {
    if (m > n || m < 0) return 0; // 边界条件
    long long ans = fac[n];
    ans = (ans * inv[m]) % MOD;
    ans = (ans * inv[n - m]) % MOD;
    return (int)ans;
}

// 组合公式 C(n, m) % MOD
// 直接计算，不使用阶乘表和逆元表
//暴力算法
int c1(int n, int m) {
    if (m > n || m < 0) return 0; // 边界条件
    long long ans = 1;
    for (int i = 1; i <= m; i++) {
        ans = (ans * (n - m + i)) % MOD;
        ans = (ans * power(i, MOD - 2)) % MOD; // 乘以 i 的逆元
    }
    return (int)ans;
}

int main() {
    cout << "测试开始" << endl;
    build();

    // 测试 c1 和 c2 的一致性
    int n = 500;
    for (int m = 0; m <= n; m++) {
        int ans1 = c1(n, m);
        int ans2 = c2(n, m);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
        else{
            cout<<"第 "<<setw(3)<<m<<" 组测试通过！"<<endl;
        }
    }
    cout << "测试结束" << endl;

    // 计算 C(a, b) % MOD
    int a = 537;
    int b = 367;
    cout << "计算 C(" << a << ", " << b << ") % " << MOD << endl;
    cout << "方法1答案: " << c1(a, b) << endl;
    cout << "方法2答案: " << c2(a, b) << endl;

    return 0;
}