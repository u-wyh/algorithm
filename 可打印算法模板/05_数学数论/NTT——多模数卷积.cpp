// 用途：多项式系数按任意给定模数取模时，求两多项式的卷积。
// 时间：O(L log L)，L 是不小于 n+m+1 的最小二次幂。
// 空间：O(L)，使用静态数组；NTT 保留递归写法。
// 注意：这里 n,m≤1e5，1≤mod≤1e9；卷积整数系数上界必须小于三个 NTT 质数的乘积。
// 例题：https://www.luogu.com.cn/problem/P4245
// 题意：给两个多项式和一个不适合直接 NTT 的模数，求乘积的系数。
// 思路：在三个 NTT 质数下分别卷积，再用 CRT 还原整数系数并对目标模数取余。
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128_t;
const int MAXN = 100005, MAXT = 1 << 19;
const long long P[3] = {998244353, 1004535809, 469762049};
const long long GI[3] = {332748118, 334845270, 156587350}; // 原根 3 的逆元。
long long a[MAXN], b[MAXN], A[MAXT], B[MAXT], temp[MAXT], rems[3][MAXT];

long long qpow(long long x, long long e, long long mod) {
    long long result = 1;
    while (e) {
        if (e & 1) result = result * x % mod;
        x = x * x % mod;
        e >>= 1;
    }
    return result;
}

// 把偶数项、奇数项写入 scratch；递归结果仍落在 scratch，最后合并回 data。
// 交替使用两块静态数组，避免每层递归创建变长数组。
void ntt(long long data[], long long scratch[], int len, bool inverse,
         long long mod, long long inverseRoot) {
    if (len == 1) return;
    int half = len / 2;
    for (int i = 0; i < half; ++i) {
        scratch[i] = data[i * 2];
        scratch[i + half] = data[i * 2 + 1];
    }
    ntt(scratch, data, half, inverse, mod, inverseRoot);
    ntt(scratch + half, data + half, half, inverse, mod, inverseRoot);
    long long root = qpow(inverse ? inverseRoot : 3, (mod - 1) / len, mod);
    long long omega = 1;
    for (int i = 0; i < half; ++i) {
        long long v = scratch[i + half] * omega % mod;
        data[i] = (scratch[i] + v) % mod;
        data[i + half] = (scratch[i] - v + mod) % mod;
        omega = omega * root % mod;
    }
}

void print128(i128 x) {
    if (x >= 10) print128(x / 10);
    cout << char('0' + x % 10);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long mod;
    cin >> n >> m >> mod;
    for (int i = 0; i <= n; ++i) cin >> a[i];
    for (int i = 0; i <= m; ++i) cin >> b[i];
    int len = 1;
    while (len < n + m + 1) len <<= 1;

    for (int k = 0; k < 3; ++k) {
        fill(A, A + len, 0);
        fill(B, B + len, 0);
        for (int i = 0; i <= n; ++i) A[i] = a[i] % P[k];
        for (int i = 0; i <= m; ++i) B[i] = b[i] % P[k];
        ntt(A, temp, len, false, P[k], GI[k]);
        ntt(B, temp, len, false, P[k], GI[k]);
        for (int i = 0; i < len; ++i) A[i] = A[i] * B[i] % P[k];
        ntt(A, temp, len, true, P[k], GI[k]);
        long long invlen = qpow(len, P[k] - 2, P[k]);
        for (int i = 0; i <= n + m; ++i) rems[k][i] = A[i] * invlen % P[k];
    }

    // CRT 系数只与质数有关，预处理后逐项还原。
    i128 product = (i128)P[0] * P[1] * P[2];
    i128 coeff[3];
    for (int k = 0; k < 3; ++k) {
        i128 part = product / P[k];
        coeff[k] = part * qpow((long long)(part % P[k]), P[k] - 2, P[k]) % product;
    }
    for (int i = 0; i <= n + m; ++i) {
        i128 value = 0;
        for (int k = 0; k < 3; ++k)
            value = (value + rems[k][i] * coeff[k]) % product;
        if (i) cout << ' ';
        print128(value % mod);
    }
    cout << '\n';
}
