#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[m+1][n+1];
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }

    int dp[m+1][n+1];
    for(int i=1;i<=m;i++)
        dp[i][1]=nums[i][1];
    dp[0][1]=dp[m][1];
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dp[j][i]=min(dp[j-1][i-1],dp[j][i-1])+nums[j][i];
            if(j==m)
                dp[0][i]=dp[j][i];
        }
    }
    int ans=INT_MAX;
    for(int i=1;i<=m;i++)
    {
        ans=min(ans,dp[i][n]);
    }
    printf("%d\n",ans);
    return 0;
}
