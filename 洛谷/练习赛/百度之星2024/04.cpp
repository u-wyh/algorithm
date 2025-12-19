#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MOD = 998244353;

int n,k;
int dp[2][MAXN][7];
char s[MAXN];

int main()
{
    scanf("%d %d",&n,&k);
    scanf("%s",s+1);
    dp[0][1][0]=1;
    for(int i=1;i<=n;i++){
        int u=i&1;
        int v=1-u;
        for(int j=1;j<=min(i,k)+1;j++){
            if(s[i]=='0'){
                dp[u][j][0]=(dp[v][j][0]+dp[v][j][4])%MOD;
                dp[u][j][1]=(dp[v][j-1][0]+dp[v][j-1][4])%MOD;
                dp[u][j][2]=(dp[v][j][1]+dp[v][j][5])%MOD;
                dp[u][j][3]=(dp[v][j-1][1]+dp[v][j-1][5])%MOD;
                dp[u][j][4]=(dp[v][j][2])%MOD;
                dp[u][j][5]=(dp[v][j-1][2])%MOD;
                dp[u][j][6]=(dp[v][j-1][3]+dp[v][j-1][6])%MOD;
            }
            else{
                dp[u][j][0]=(dp[v][j-1][0]+dp[v][j-1][4])%MOD;
                dp[u][j][1]=(dp[v][j][0]+dp[v][j][4])%MOD;
                dp[u][j][2]=(dp[v][j-1][1]+dp[v][j-1][5])%MOD;
                dp[u][j][3]=(dp[v][j][1]+dp[v][j][5])%MOD;
                dp[u][j][4]=(dp[v][j-1][2])%MOD;
                dp[u][j][5]=(dp[v][j][2])%MOD;
                dp[u][j][6]=(dp[v][j][3]+dp[v][j][6])%MOD;
            }
        }
    }
    int ans=0;
    int u=n&1;
    for(int i=1;i<=min(n,k)+1;i++){
        for(int j=0;j<=6;j++){
            ans=(ans+dp[u][i][j])%MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}