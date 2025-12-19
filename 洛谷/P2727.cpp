#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,len,m;
int dp[35][35];

signed main()
{
    cin>>n>>len>>m;
    for(int i=0;i<=len;i++){
        dp[0][i]=1;
    }
    for(int i=1;i<=n;i++){
        dp[i][0]=1;
        for(int j=1;j<=len;j++){
            dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
        }
    }
    for(int i=n;i>=1;i--){
        int ans=0;
        if(dp[i-1][len]<m){
            ans=1;
            m-=dp[i-1][len];
            len--;
        }
        cout<<ans;
    }
    return 0;
}