#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int n,m;
int dp[2][10005];

int compute(int n,int m){
    int ans=1;
    for(int i=1;i<=min(m,n-m);i++){
        ans*=(n-i+1);
        ans/=i;
        ans%=MOD;
    }
    return ans;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        if(a==-1){
            m++;
        }
    }
    n=n-m;
    if(n<=m){
        cout<<compute(m+1,n)<<endl;
        return 0;
    }
    dp[0][0]=1;
    for(int i=1;i<=(m+n);i++){
        for(int j=0;j<=(n-m);j++){
            int op=i&1;
            if(j==0)
                dp[op][j]=dp[op^1][j+1]%MOD;
            else
                dp[op][j]=(dp[op^1][j-1]+dp[op^1][j+1])%MOD;
        }
    }
    cout<<dp[(n+m)&1][n-m]<<endl;
    return 0;
}
