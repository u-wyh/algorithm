#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e4+7;
const int MAXN = 128;

int n,m;
int dp[MAXN][MAXN];

int main()
{
    cin>>n>>m;
    for(int i=0;i<=m;i++){
        dp[0][i]=1,dp[1][i]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<i;k++){
                dp[i][j]=(dp[i][j]+(dp[k][m]*dp[i-k][j-1])%MOD)%MOD;
            }
        }
    }
    cout<<dp[n][m]<<endl;
    return 0;
}