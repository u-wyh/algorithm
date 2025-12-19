#include<stdio.h>
#include<limits.h>
#include<string.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&b[i]);
    }
    int dp[n+1][m+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=INT_MAX;
        }
    }
    for(int i=0;i<=m;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=m;j++)
        {
            //dp[i][j]=min(dp[i][j],dp[i-1][j]);
            dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+a[i]*b[j]);
        }
    }
    int ans=INT_MAX;
    for(int i=n;i<=m;i++)
        ans=min(ans,dp[n][i]);
    printf("%d\n",ans);
    return 0;
}
