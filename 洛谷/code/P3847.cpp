#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int n;
int dp[MAXN][MAXN];
int arr[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        dp[i][i]=0;
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            if(arr[i]==arr[j]){
                dp[i][j]=dp[i+1][j-1];
            }
            else{
                dp[i][j]=min(min(dp[i+1][j],dp[i][j-1]),dp[i+1][j-1])+1;
            }
        }
    }
    cout<<dp[1][n]<<endl;
    return 0;
}
