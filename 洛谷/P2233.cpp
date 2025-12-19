//P2233
#include<bits/stdc++.h>
using namespace std;

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
                ans[i][j]%=1000;
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

int main()
{
    vector<vector<int>>base={{0,2,0,0},{1,0,1,0},{0,1,0,1},{0,0,1,0}};
    vector<vector<int>>m={{1},{0},{0},{0}};
    int n;
    cin>>n;
    vector<vector<int>> base_pow = power(base, n-1); // 计算 base 的 n 次幂
    m = multiply(base_pow, m); // 与 m 相乘
//    for(int i=0;i<4;i++){
//        cout<<m[i][0]<<' ';
//    }
//    cout<<endl;
    cout<<m[3][0]*2%1000<<endl;
    return 0;
}
