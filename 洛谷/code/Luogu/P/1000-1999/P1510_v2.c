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
    int dp[c+1];
    for(int i=0;i<=c;i++)
        dp[i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=c;j>=0;j--)
        {
            if(j>=cost[i])
                dp[j]=max(dp[j],dp[j-cost[i]]+val[i]);
        }
    }
    for(int i=0;i<=c;i++)
    {
        if(dp[i]>=v)
        {
            printf("%d\n",c-i);
            return 0;
        }
    }
    printf("Impossible\n");
    return 0;
}

