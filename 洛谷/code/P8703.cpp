#include<bits/stdc++.h>
using namespace std;

string s,t;
int dp[1005][1005];
int n,m;

int main()
{
    cin>>s>>t;
    n=s.length(),m=t.length();
    for(int i=0;i<=n;i++){
        dp[i][0]=0;
    }
    for(int i=0;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=1e9;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1]==t[j-1]){
                dp[i][j]=dp[i-1][j-1];
            }
            else{
                dp[i][j]=min(dp[i-1][j-1]+1,dp[i-1][j]);
            }
        }
    }
    cout<<dp[n][m]<<endl;
    return 0;
}
