#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 16;

int n,m,mod;
int b[MAXN],c[MAXN];

vector<vector<int>> multiply(vector<vector<int>> a,const vector<vector<int>> b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k;
    cin>>k;
    int all=0;
    for(int i=1;i<=k;i++){
        cin>>b[i];
        all+=b[i];
    }
    for(int i=1;i<=k;i++){
        cin>>c[i];
    }
    vector<vector<int>>base1(k+1,vector<int>(k+1,0));
    vector<vector<int>>base2(k+1,vector<int>(1,0));
    base2[0][0]=all;
    for(int i=1;i<=k;i++){
        base2[i][0]=b[k-i+1];
    }
    base1[0][0]=1;
    for(int i=1;i<=k;i++){
        base1[0][i]=c[i];
        base1[1][i]=c[i];
    }
    for(int i=2;i<=k;i++){
        base1[i][i-1]=1;
    }
    cin>>m>>n>>mod;
    int ans=0;
    if(m-1>=k){
        vector<vector<int>>ans1=multiply(power(base1,m-1-k),base2);
        ans-=ans1[0][0];
    }
    else{
        for(int i=1;i<=m-1;i++){
            ans-=b[i];
        }
    }
    if(n>=k){
        vector<vector<int>>ans2=multiply(power(base1,n-k),base2);
        ans+=ans2[0][0];
    }
    else{
        for(int i=1;i<=n;i++){
            ans+=b[i];
        }
    }
    ans=(ans%mod+mod)%mod;
    cout<<ans<<endl;
    return 0;
}