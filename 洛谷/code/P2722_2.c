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
    int dp[m+1];
    for(int i=0;i<=m;i++)
        dp[i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=0;j--)
        {
            for(int k=1;k*cost[i]<=j;k++)
            {
                dp[j]=max(dp[j],dp[j-k*cost[i]]+k*val[i]);
            }
        }
    }
    printf("%d\n",dp[m]);
    return 0;
}
