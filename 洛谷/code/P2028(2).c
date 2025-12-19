#include<stdio.h>

int main()
{
    unsigned long long n,k,p;
    scanf("%llu %llu %llu",&n,&k,&p);
    unsigned long long dp[n+1][k+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=k;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        dp[i][1]=1;
        for(int j=2;j<=k;j++)
        {
            dp[i][j]=(dp[i-1][j-1]%p+(dp[i-1][j]%p)*(j%p))%p;
        }
    }
    printf("%llu\n",dp[n][k]);
    return 0;
}
