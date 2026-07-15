#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+2];
    nums[0]=0;
    nums[n+1]=0;
    for(int i=1;i<=n;i++)
        scanf("%d",&nums[i]);
    int dp[n+1][n+2];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n+1;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=n;j>=i;j--)
        {
            int count=n-(j-i+1);
            dp[i][j]=max(dp[i-1][j]+nums[i-1]*count,dp[i][j+1]+count*nums[j+1]);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=max(ans,dp[i][i]+n*nums[i]);
    }
    printf("%d\n",ans);
    return 0;
}
