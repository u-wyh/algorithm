#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int INF = 1e9;

int n,m;
int dp[MAXN][MAXN][2];
int val[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j][0]=dp[i][j][1]=-INF;
        }
    }
    dp[0][0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
            if(j>=1){
                dp[i][j][1]=max(dp[i-1][j][1],dp[i-1][j-1][0])+val[i];
            }
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        ans=max(ans,max(dp[n][i][0],dp[n][i][1]));
    }
    cout<<ans<<endl;
    return 0;
}