#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n;
int arr[MAXN];
int dp[MAXN][MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        arr[i]+=arr[i-1];
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<=n-i+1;j++){
            int k=arr[n]-arr[i-1]-dp[i+j][min(j*2,n-i-j+1)];
            dp[i][j]=max(dp[i][j-1],k);
        }
    }
    cout<<dp[1][2]<<endl;
    return 0;
}
