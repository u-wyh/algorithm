// 用途：求多项式 A(x) 在模 x^n 意义下的乘法逆元 B(x)。
// 时间：O(n log n)，逐层倍增求逆。
// 空间：O(n)，静态数组；NTT 和倍增过程都采用递归。
// 注意：模数固定为 998244353；A 的常数项非零；n≤200000。
// 例题：https://www.luogu.com.cn/problem/P4238
// 题意：给 A(x)，输出前 n 项 B(x)，使 A(x)B(x)≡1 (mod x^n)。
// 思路：已知前一半的逆元 B，用 B_new=B(2-AB) 把正确位数翻倍。
#include <bits/stdc++.h>
using namespace std;
const long long MOD = 998244353, GINV = 332748118;
const int MAXT = 1 << 19;
long long a[MAXT], b[MAXT], A[MAXT], B[MAXT], temp[MAXT];

long long qpow(long long x, long long e) {
    long long result = 1;
    while (e) {
        if (e & 1) result = result * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return result;
}

// 偶奇分治；data 和 scratch 交替使用，递归中不创建大栈数组。
void ntt(long long data[], long long scratch[], int len, bool inverse) {
    if (len == 1) return;
    int half = len / 2;
    for (int i = 0; i < half; ++i) {
        scratch[i] = data[i * 2];
        scratch[i + half] = data[i * 2 + 1];
    }
    ntt(scratch, data, half, inverse);
    ntt(scratch + half, data + half, half, inverse);
    long long root = qpow(inverse ? GINV : 3, (MOD - 1) / len);
    long long omega = 1;
    for (int i = 0; i < half; ++i) {
        long long v = scratch[i + half] * omega % MOD;
        data[i] = (scratch[i] + v) % MOD;
        data[i + half] = (scratch[i] - v + MOD) % MOD;
        omega = omega * root % MOD;
    }
}

// n 是 2 的幂；先求低 n/2 项，再补足到 n 项。
void polynomialInverse(int n) {
    if (n == 1) {
        b[0] = qpow(a[0], MOD - 2);
        return;
    }
    polynomialInverse(n / 2);
    int len = n * 2;
    for (int i = 0; i < len; ++i) {
        A[i] = i < n ? a[i] : 0;
        B[i] = i < n / 2 ? b[i] : 0;
    }
    ntt(A, temp, len, false);
    ntt(B, temp, len, false);
    for (int i = 0; i < len; ++i)
        A[i] = B[i] * ((2 - A[i] * B[i] % MOD + MOD) % MOD) % MOD;
    ntt(A, temp, len, true);
    long long invlen = qpow(len, MOD - 2);
    for (int i = 0; i < n; ++i) b[i] = A[i] * invlen % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int padded = 1;
    while (padded < n) padded <<= 1;
    polynomialInverse(padded);
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << b[i];
    }
    cout << '\n';
}
