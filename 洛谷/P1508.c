#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int nums[m+2][n+1];
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    for(int i=0;i<=n;i++)
        nums[m+1][i]=0;
    int dp[m+2][n+2];
    for(int i=0;i<=m+1;i++)
    {
        for(int j=0;j<=n+1;j++)
        {
            dp[i][j]=INT_MIN/2;
        }
    }
    dp[m+1][(n+1)/2]=nums[m+1][(n+1)/2];
    for(int i=m;i>=1;i--)
    {
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=max(max(dp[i+1][j],dp[i+1][j+1]),dp[i+1][j-1])+nums[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[1][i]);
    printf("%d\n",ans);
    return 0;
}
