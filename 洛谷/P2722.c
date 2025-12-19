#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int cost[n+1],val[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&val[i],&cost[i]);
    }
    int dp[n+1][m+1];
    for(int i=0;i<=m;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k*cost[i]<=j;k++)
            {
                dp[i][j]=max(dp[i][j],dp[i-1][j-cost[i]*k]+k*val[i]);
            }
        }
    }
    printf("%d\n",dp[n][m]);
    return 0;
}
