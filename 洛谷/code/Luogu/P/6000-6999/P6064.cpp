#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3900;

int dp[MAXN][MAXN][2];
int n,m,ans;
int arr[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j][0]=dp[i][j][1]=INT_MIN;
        }
    }
    dp[1][1][1]=0;
    dp[1][0][0]=0;
    for(int i=2;i<=n;i++){
        dp[i][0][0]=dp[i-1][0][0];
        for(int j=1;j<=m;j++){
            dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+arr[i]);
            dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
        }
    }
    ans=max(dp[n][m][0],dp[n][m][1]);
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j][1]=dp[i][j][0]=INT_MIN;
        }
    }
    dp[1][1][1]=arr[1];
    dp[1][0][0]=0;
    for(int i=2;i<=n;i++){
        dp[i][0][0]=dp[i-1][0][0];
        for(int j=1;j<=m;j++){
            dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+arr[i]);
            dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
        }
    }
    ans=max(ans,dp[n][m][1]);
    cout<<ans<<endl;
    return 0;
}
