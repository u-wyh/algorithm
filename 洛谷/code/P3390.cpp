// https://www.luogu.com.cn/problem/P3390
// 题意：输入矩阵阶数 n、幂次 k，以及 n×n 整数矩阵 A。
// 计算矩阵的 k 次幂 A^k。
// 输出 n 行 n 列的矩阵，每个元素对 10^9+7 取模。
// 数据范围：1 <= n <= 100，0 <= k <= 10^12，|A_{i,j}| <= 1000。
#include<bits/stdc++.h>
// 算法标签：矩阵快速幂、矩阵乘法
using namespace std;
#define int long long
const int MOD = 1e9+7;

// 矩阵相乘
// a的列数一定要等于b的行数
vector<vector<int>> multiply(vector<vector<int>>& a,const vector<vector<int>>& b) {
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

signed main()
{
    int n,p;
    cin>>n>>p;
    vector<vector<int>>base(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>base[i][j];
        }
    }
    vector<vector<int>> base_pow = power(base, p);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<base_pow[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}

