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
        long long dp[heat[i]+1];
        for(int k=0;k<=heat[i];k++)
        {
            dp[k]=0;
        }
        for(int k=1;k<=count[i];k++)
        {
            for(int l=heat[i];l>=0;l--)
            {
                if(l>=cost[left[i]+k-1])
                    dp[l]=max(dp[l],dp[l-cost[left[i]+k-1]]+val[left[i]+k-1]);
            }
        }
        printf("%lld\n",dp[heat[i]]);
    }
    return 0;
}
