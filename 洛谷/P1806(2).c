#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    long long dp[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
            if(i==j)
                dp[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j < i;j++)
        {
            for(int k=1 ;k < j&& k <= i - j; k ++ )
            {
                dp[i][j]+=dp[i-j][k];
            }
        }
    }
    long long ans=0;
    for(int i=1;i<n;i++)
        ans+=dp[n][i];
    printf("%lld\n",ans);
    return 0;
}
