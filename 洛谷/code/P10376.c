#include<stdio.h>
#define mod 1000000007

long long dp[200005];

int main()
{
    int n,a,b,c;
    scanf("%d %d %d %d",&n,&a,&b,&c);
    for(int i=0;i<200005;i++)
        dp[i]=0;
    dp[n]=1;
    for(int i=n-1;i>=0;i--)
    {
        if(i+a<=n&&i+a>c)
            dp[i]=(dp[i]+dp[i+a])%mod;
        if(i+b<=n&&i+b>c)
            dp[i]=(dp[i]+dp[i+b])%mod;
    }
    long long ans=0;
    for(int i=0;i<=c;i++)
    {
        ans=(ans+dp[i])%mod;
    }
    printf("%lld\n",ans);
    return 0;
}
