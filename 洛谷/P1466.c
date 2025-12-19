#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int sum=(n*n+n)/2;
    if(sum%2==0)
        sum/=2;
    else
    {
        int ans=0;
        printf("%d\n",ans);
        return 0;
    }
    long long dp[n+1][sum+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=0;
        }
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=i)
                dp[i][j]+=dp[i-1][j-i];
        }
    }
    printf("%lld\n",dp[n][sum]/2);
    return 0;
}
