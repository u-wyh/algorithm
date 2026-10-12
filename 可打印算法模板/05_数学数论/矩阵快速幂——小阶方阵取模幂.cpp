// 用途：计算小阶方阵 A 的非负整数次幂 A^e（模 mod），用于线性状态转移加速。
// 时间：O(k³ log e)，k 为矩阵阶数。
// 空间：O(k²)。
// 注意：k≤50，0≤e≤10^18，1≤mod≤10^9+7；输入系数可为负数。
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 51;
struct Matrix {
    long long a[MAXK][MAXK] = {};
};

Matrix multiply(const Matrix &left, const Matrix &right, int k, long long mod) {
    Matrix result;
    for (int i = 0; i < k; ++i) {
        for (int t = 0; t < k; ++t) {
            if (left.a[i][t] == 0) continue;
            for (int j = 0; j < k; ++j) {
                result.a[i][j] = (result.a[i][j] +
                                  left.a[i][t] * right.a[t][j] % mod) % mod;
            }
        }
    }
    return result;
}

Matrix power(Matrix base, long long exponent, int k, long long mod) {
    Matrix result;
    for (int i = 0; i < k; ++i) result.a[i][i] = 1 % mod;
    while (exponent > 0) {
        if (exponent & 1) result = multiply(result, base, k, mod);
        exponent >>= 1;
        if (exponent > 0) base = multiply(base, base, k, mod);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    long long exponent, mod;
    cin >> k >> exponent >> mod;
    Matrix base;
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j) {
            cin >> base.a[i][j];
            base.a[i][j] = (base.a[i][j] % mod + mod) % mod;
        }
    Matrix result = power(base, exponent, k, mod);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j)
            cout << result.a[i][j] << (j + 1 == k ? '\n' : ' ');
    }
    return 0;
}
