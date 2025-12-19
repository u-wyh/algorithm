//P2106
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

// 矩阵相乘
// a的列数一定要等于b的行数
vector<vector<long long>> multiply(vector<vector<long long>>& a,const vector<vector<long long>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<long long>> ans(n, vector<long long>(m, 0));
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
vector<vector<long long>> power(vector<vector<long long>>& m, long long p) {
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

int main()
{
    long long k;
    cin>>k;
    if(k==1){
        cout<<10<<endl;
        return 0;
    }
    vector<vector<long long>>base;
    base.resize(10, vector<long long>(10, 0));
    base[0] = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    base[1] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    base[2] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
    base[3] = {0, 1, 1, 1, 1, 1, 0, 0, 0, 0};
    base[4] = {0, 0, 1, 1, 1, 1, 1, 0, 0, 0};
    base[5] = {0, 0, 0, 1, 1, 1, 1, 1, 0, 0};
    base[6] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 0};
    base[7] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
    base[8] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
    base[9] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
    vector<vector<long long>>m={{0,1,1,1,1,1,1,1,1,1}};
    m = multiply(m,power(base, k-1));
    long long ans=0;
    for(int i=0;i<=9;i++){
        ans+=((m[0][i]%MOD)+MOD)%MOD;
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}
