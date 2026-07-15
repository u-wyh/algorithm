#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m,d,s;
    scanf("%d %d %d %d",&n,&m,&d,&s);
    int a[m+1],b[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
    }
    int dp[m+1][n+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=1e9;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k<=b[i];k++)
            {
                dp[i][j]=min(dp[i][j],dp[i-1][j-k]+k*a[i]+d);
            }
        }
    }
    if(dp[m][n]>=1e9)
        printf("impossible\n");
    else
        printf("%d\n",dp[m][n]);
    return 0;
}
