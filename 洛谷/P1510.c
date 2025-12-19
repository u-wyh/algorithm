#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int v,n,c;
    scanf("%d %d %d",&v,&n,&c);
    int val[n+1],cost[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&val[i],&cost[i]);
    }
    int dp[n+1][c+1];
    for(int i=0;i<=c;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=c;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=cost[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-cost[i]]+val[i]);
        }
    }
    for(int i=0;i<=c;i++)
    {
        if(dp[n][i]>=v)
        {
            printf("%d\n",c-i);
            return 0;
        }
    }
    printf("Impossible\n");
    return 0;
}
