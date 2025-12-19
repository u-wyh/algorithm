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
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&cost[i]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&val[i]);
    }

    int left[m+1],right[m+1],heat[m+1],count[m+1];

    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&left[i],&right[i],&heat[i]);
        count[i]=right[i]-left[i]+1;
    }
    for(int i=1;i<=m;i++)
    {
        long long dp[count[i]+1][heat[i]+1];
        for(int j=0;j<=count[i];j++)
        {
            for(int k=0;k<=heat[i];k++)
            {
                dp[j][k]=0;
            }
        }
        for(int k=1;k<=count[i];k++)
        {
            for(int l=0;l<=heat[i];l++)
            {
                dp[k][l]=dp[k-1][l];
                if(l>=cost[left[i]+k-1])
                    dp[k][l]=max(dp[k][l],dp[k-1][l-cost[left[i]+k-1]]+val[left[i]+k-1]);
            }
        }
        printf("%lld\n",dp[count[i]][heat[i]]);
    }
    return 0;
}
