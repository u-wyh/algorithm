#include<bits/stdc++.h>
using namespace std;

int n,m;
int dp[105][105];//dp[i][j]表示前i个人完成了j个任务一的情况下最多可以完成任务二的数量
int d1[105];
int d2[105];

bool check(int limit){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=INT_MIN;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=j&&(limit>=k*d1[i]);k++){
                dp[i][j]=max(dp[i][j],dp[i-1][j-k]+(limit-k*d1[i])/d2[i]);
            }
        }
    }
    return dp[n][m]>=m;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>d1[i]>>d2[i];
    }
    int l=0,r=10000,ans=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}