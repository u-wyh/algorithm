#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int cost[n+1],val[n+1];
    int dp[m+1];
    for(int i=0;i<=m;i++)
        dp[i]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&cost[i],&val[i]);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=0;j--)
        {
            if(j>=cost[i])
                dp[j]=max(dp[j],dp[j-cost[i]]+val[i]);
        }
    }
    printf("%d\n",dp[m]);
    return 0;
}

