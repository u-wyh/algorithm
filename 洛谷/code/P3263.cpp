#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 7528443412579576937;

int b,d,n;

int add(int a, int b) {
    a %= MOD;
    b %= MOD;
    if (a > MOD - b) {
        return a - (MOD - b);
    } else {
        return a + b;
    }
}

int mul(int a,int b){
    a%=MOD;
    b%=MOD;
    int ans=0;
    while(b){
        if(b&1){
            ans=add(ans,a);
        }
        b>>=1;
        a=add(a,a);
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
                ans[i][j] = add(ans[i][j],mul(a[i][c] , b[c][j]));
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
    cin>>b>>d>>n;
    if(n==0){
        cout<<1<<endl;
        return 0;
    }
    vector<vector<int>>base(2,vector<int>(2,0));
    vector<vector<int>>vec(1,vector<int>(2,0));
    vec[0][0]=b,vec[0][1]=2;
    base={{b,1},{(d-b*b)/4,0}};
    // cout<<888<<endl;
    vec=multiply(vec,power(base,n-1));
    int ans=vec[0][0];
    if(d!=b*b){
        if(n%2==0){
            ans--;
        }
    }
    ans=add(ans,MOD);
    cout<<ans<<endl;
    return 0;
}