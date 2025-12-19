#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244352;
const int mod = 998244353;

int n;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        b>>=1;
        a=(a*a)%mod;
    }
    return ans;
}

vector<vector<int>> multiply(vector<vector<int>> a,const vector<vector<int>> b) {
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
vector<vector<int>> power(vector<vector<int>> m, int p) {
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
    cin>>n;
    if(n==1){
        cout<<2<<endl;
        return 0;
    }
    if(n==2){
        cout<<6<<endl;
        return 0;
    }
    vector<vector<int>>vec={{1,0}};
    vector<vector<int>>base={{1,1},{1,0}};
    // for(int i=1;i<=10;i++){
    //     cout<<multiply(vec,power(base,i))[0][0]<<endl;
    // }
    int a=multiply(vec,power(base,n-1))[0][0];
    int b=multiply(vec,power(base,n))[0][0];
    // cout<<a<<' '<<b<<endl;
    b=(b-1+MOD)%MOD;
    int ans=(power(2,a)*power(3,b))%mod;
    ans=(ans+mod)%mod;
    cout<<ans<<endl;
    return 0;
}