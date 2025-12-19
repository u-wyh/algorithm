#include<bits/stdc++.h>
using namespace std;

int n;
int nums[1005];
int dp[1005][1005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            if(j>0){
                dp[i][j]=dp[i-1][j-1];
            }
            dp[i][j]=max(dp[i][j],dp[i-1][j]+(nums[i]==i-j));
        }
    }
    int ans=0;
    for(int j=0;j<=n;j++){
        ans=max(ans,dp[n][j]);
    }
    cout<<ans;
    return 0;
}
