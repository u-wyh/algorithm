#include<stdio.h>
#include<math.h>
#include<limits.h>

long long min(long long  a,long long  b)
{
    return a<b?a:b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
    }
    long long dp[n+1][m+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=INT_MAX/2;
            if(j==0)
                dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=1;j--)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k<=j;k++)
                dp[i][j]=min(dp[i][j],dp[i-1][j-k]+a[i]*pow(k,b[i]));
        }
    }
    /*for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            printf("%5d",dp[i][j]);
        }
        printf("\n");
    }*/
    printf("%lld\n",dp[n][m]);
    return 0;
}
