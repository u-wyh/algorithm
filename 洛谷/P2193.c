#include<stdio.h>
#define mod 1000000007

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int dp[k+1][n+1];
    for(int i=0;i<=k;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        dp[1][i]=1;
    }
    for(int i=2;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int m=1;m<=n/j;m++)
                dp[i][m*j]=(dp[i][m*j]+dp[i-1][j])%mod;
        }
    }
    int ans=dp[k][1];
    for(int i=2;i<=n;i++)
        ans=(ans+dp[k][i])%mod;
    printf("%d\n",ans);
    return 0;
}
