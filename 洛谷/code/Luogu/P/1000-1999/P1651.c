#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,sum=0;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    int dp[n+1][sum];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=INT_MIN;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=max(dp[i-1][j],dp[i-1][j+nums[i]]);
            if(j>=nums[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-nums[i]]+nums[i]);
            else
                dp[i][j]=max(dp[i][j],dp[i-1][nums[i]-j]+j);
        }
    }
    if(dp[n][0]>0)
    {
        printf("%d\n",dp[n][0]);
        return 0;
    }
    printf("-1\n");
    return 0;
}
