#include<bits/stdc++.h>
using namespace std;

int n;
int nums[5005];
int dp[5005];
int sum[5005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        sum[i]=sum[i-1]+nums[i];
        dp[i]=nums[i];
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            dp[i]=sum[j]-sum[i-1]-min(dp[i+1],dp[i]);
        }
    }
    cout<<dp[1]<<endl;
    return 0;
}

