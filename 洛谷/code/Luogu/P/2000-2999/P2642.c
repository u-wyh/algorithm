#include<stdio.h>
#include<limits.h>

long long max(long long  a,long long b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    long long nums[n+1];
    long long Max[n+1];
    Max[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&nums[i]);
        Max[i]=nums[i];
        if(Max[i-1]>0)
            Max[i]+=Max[i-1];
    }
    long long Max2[n+1];
    Max2[n]=nums[n];
    for(int i=n-1;i>=1;i--)
    {
        Max2[i]=nums[i];
        if(Max2[i+1]>0)
            Max2[i]+=Max2[i+1];
    }
    long long dp[n+1];
    dp[n]=Max2[n];
    for(int i=n-1;i>=1;i--)
    {
        dp[i]=INT_MIN;
        dp[i]=max(dp[i+1],Max2[i]);
    }
    long long ans=INT_MIN;
    for(int i=1;i<=n-2;i++)
    {
        ans=max(ans,Max[i]+dp[i+2]);
    }
    printf("%lld\n",ans);
    return 0;
}
