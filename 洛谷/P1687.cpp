#include<bits/stdc++.h>
using namespace std;

int n,k;
int nums[3005];
int cnt=0;
int dp[3005][3005][2];

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>nums[++cnt];
        if(nums[cnt]>119)
            cnt--;
    }
    //cout<<cnt<<endl;
    if(cnt<k){
        cout<<"You can't do it."<<endl;
        return 0;
    }
    for(int i=0;i<=cnt;i++){
        //cout<<nums[i]<<' ';
        for(int j=0;j<=k;j++){
            dp[i][j][0]=1e9;
            dp[i][j][1]=1e9;
        }
    }
    //cout<<endl;
    for(int i=0;i<=cnt;i++){
        dp[i][0][1]=0;
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=min(i,k);j++){
            dp[i][j][0]=dp[i-1][j][0];
            dp[i][j][1]=dp[i-1][j][1];//表示不要

            if(dp[i-1][j-1][0]+nums[i]>119){
                if(dp[i-1][j-1][1]+1<dp[i][j][1])
					dp[i][j][1]=dp[i-1][j-1][1]+1,dp[i][j][0]=nums[i];
				else if(dp[i-1][j-1][1]+1==dp[i][j][1])
					dp[i][j][0]=min(nums[i],dp[i][j][0]);
            }
            else{
                if(dp[i-1][j-1][1]<dp[i][j][1])
					dp[i][j][1]=dp[i-1][j-1][1],dp[i][j][0]=dp[i-1][j-1][0]+nums[i];
				else if(dp[i-1][j-1][1]==dp[i][j][1])
					dp[i][j][0]=min(dp[i-1][j-1][0]+nums[i],dp[i][j][0]);
            }
        }
    }
    cout<<dp[cnt][k][1]<<endl;
    return 0;
}
