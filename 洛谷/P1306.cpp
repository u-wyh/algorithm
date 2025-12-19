#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e8;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 矩阵相乘
// a的列数一定要等于b的行数
vector<vector<int>> multiply(vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]%=MOD;
            }
        }
    }
    return ans;
}


// 矩阵快速幂
vector<vector<int>> power(vector<vector<int>>& m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//单位矩阵 相当于乘法快速幂中的1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//每次都是倍增
    }
    return ans;
}

// 时间复杂度O(logn)，矩阵快速幂的解法
int fib2(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    // 定义初始矩阵和转移矩阵
    vector<vector<int>> start = { {1, 0} };
    vector<vector<int>> base = {
        {1, 1},
        {1, 0}
    };

    // 计算矩阵快速幂
    vector<vector<int>> ans = multiply(start, power(base, n - 1));
    return ans[0][0];
}

signed main() {
    int n,m;
    cin >> n>>m;
    cout<<fib2(gcd(n,m))%MOD<<endl;
    return 0;
}

