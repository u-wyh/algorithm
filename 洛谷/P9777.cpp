#include<bits/stdc++.h>
using namespace std;
#define int long long
long long mod,k,n;

vector<vector<long long>> multiply(vector<vector<long long>>& a,const vector<vector<long long>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<long long>> ans(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]=((ans[i][j]%mod)+mod)%mod;
            }
        }
    }
    return ans;
}

// 矩阵快速幂
vector<vector<long long>> power(vector<vector<long long>>& m, int p) {
    int n = m.size();
    vector<vector<long long>> ans(n, vector<long long>(n, 0));
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
    cin>>mod>>k>>n;
    vector<vector<long long>>base={{k,1},{-1,0}};
    vector<vector<long long>>m={{(k*k-2)%mod,k%mod}};
    if(n==0){
        cout<<2<<endl;
        return 0;
    }
    if(n==1){
        cout<<k%mod<<endl;
        return 0;
    }
    vector<vector<long long>> base_pow = power(base, n-2);
    m = multiply(m,base_pow); // 与 m 相乘
    cout<<m[0][0]<<endl;
    return 0;
}
