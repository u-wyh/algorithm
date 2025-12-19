#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    long long dp[m+1];
    for(int i=0;i<=m;i++)
    {
        dp[i]=0;
    }
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=nums[i];j<=m;j++)
        {
            dp[j]+=dp[j-nums[i]];
        }
    }
    printf("%lld\n",dp[m]);
    return 0;
}
