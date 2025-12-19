#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    long long t,n;
    scanf("%lld %lld",&t,&n);
    int cost[n+1],val[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%lld %lld",&cost[i],&val[i]);
    }
    long long dp[n+1][t+1];
    for(int i=0;i<=t;i++)
        dp[0][i]=0;
    for(int i=0;i<=n;i++)
        dp[i][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=t;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k*cost[i]<=j;k++)
                dp[i][j]=max(dp[i][j],dp[i-1][j-k*cost[i]]+k*val[i]);
        }
    }
    printf("%lld\n",dp[n][t]);
    return 0;
}
