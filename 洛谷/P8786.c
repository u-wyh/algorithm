#include<stdio.h>
#define mod 1000000007

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int dp[n+m+1][m+1][m+1];
    for(int i=0;i<=n+m;i++)
    {
        for(int j=0;j<=m;j++)
        {
            for(int k=0;k<=m;k++)
            {
                dp[i][j][k]=0;
            }
        }
    }
    dp[0][0][2]=1;
    for(int i=0;i< m+n;i++)
    {
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<=m;k++)
            {
                if(dp[i][j][k])
                {
                    if (k > 0)
                        dp[i + 1][j + 1][k - 1] = (dp[i + 1][j + 1][k - 1] + dp[i][j][k]) % mod;
                    if(k<=50)
                        dp[i + 1][j][k * 2] = (dp[i + 1][j][k * 2] + dp[i][j][k]) % mod;
                }
            }
        }
    }
    printf("%d\n",dp[m+n][m][0]);
    return 0;
}
