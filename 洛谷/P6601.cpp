#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;

// 快速幂函数，计算 a^b % MOD
int power(int a, int b) {
    int ans = 1;
    a = a % MOD;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

// 计算模 MOD 下的逆元
int inv(int x) {
    return power(x, MOD - 2);
}

signed main() {
    int n, p, t;
    cin >> n >> p >> t;

    int inv2 = inv(2); // 1/2 的逆元
    int inv2n = inv(2 * n); // 1/(2n) 的逆元
    int invt1 = inv(t + 1); // 1/(t+1) 的逆元

    int q = ((1 - 2 * p) % MOD + MOD) % MOD;
    q = (q * q) % MOD;

    // 计算等比数列的和：sum = (q^(t+1) - 1) / (q - 1)
    int sum;
    if (q == 1) {
        // 如果 q == 1，等比数列的和为 t + 1
        sum = (t + 1) % MOD;
    } else {
        // 否则使用等比数列求和公式
        sum = q*(power(q, t + 1) - 1 + MOD) % MOD;
        sum = sum * inv(q - 1) % MOD;
    }

    // 计算答案
    int ans = (1+t + sum) % MOD; // 1 + sum
    ans = ans * inv2 % MOD; // 乘以 1/2
    ans = ans * inv2n % MOD; // 乘以 1/(2n)
    ans = ans * invt1 % MOD; // 乘以 1/(t+1)

    // 输出结果
    cout << (ans+MOD)%MOD << endl;
    return 0;
}
