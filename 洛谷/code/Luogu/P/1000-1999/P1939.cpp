//P2233
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;

vector<vector<int>> multiply(vector<vector<int>>& a,const vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]=((ans[i][j]%MOD)+MOD)%MOD;
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
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<vector<int>>base={{1,1,0},{0,0,1},{1,0,0}};
        vector<vector<int>>m={{1,1,1}};
        if(n<=3){
            cout<<1<<endl;
            continue;
        }
        vector<vector<int>> base_pow = power(base, n-3); // 计算 base 的 n 次幂
        m = multiply(m,base_pow);
        cout<<m[0][0]<<endl;
    }
    return 0;
}
