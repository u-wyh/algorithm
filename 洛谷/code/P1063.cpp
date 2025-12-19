#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n,ans=0;
int arr[MAXN<<1];
int dp[MAXN<<1][MAXN<<1];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        arr[i+n]=arr[i];
    }
    for(int k=2;k<=n;k++){
        for(int i=1;i<=2*n-k;i++){
            for(int j=i;j<=i+k-2;j++){
                dp[i][i+k-1]=max(dp[i][i+k-1],dp[i][j]+dp[j+1][i+k-1]+arr[i]*arr[i+k]*arr[j+1]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i][i+n-1]);
    }
    cout<<ans<<endl;
    return 0;
}
