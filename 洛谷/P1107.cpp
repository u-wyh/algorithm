#include<bits/stdc++.h>
using namespace std;

int n,h,delta;
int nums[2005][2005];
int dp[2005][2005];
int maxans[2005];

int main()
{
    cin>>n>>h>>delta;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int a;
            cin>>a;
            nums[i][a]++;
        }
    }
    for(int j=1;j<=h;j++){
        for(int i=1;i<=n;i++){
            dp[i][j]=max(dp[i][j-1],maxans[(j-delta)>0?(j-delta):0])+nums[i][j];
            maxans[j]=max(maxans[j],dp[i][j]);
        }
    }
    cout<<maxans[h];
    return 0;
}
