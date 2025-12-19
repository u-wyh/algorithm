#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int sum=0;
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    int dp[sum/2+1];
    for(int j=0;j<=sum/2;j++)
    {
        dp[j]=0;
        if(j==0)
            dp[j]=1;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=min(n/2,i);j>=1;j--)
        {
            for(int k=sum/2;k>=nums[i];k--)
            {
                dp[k]|=dp[k-nums[i]];
            }
        }
    }
    for(int i=sum/2;i>=0;i--)
    {
        if(dp[i])
        {
            printf("%d %d\n",i,sum-i);
            return 0;
        }
    }
    return 0;
}
