#include<stdio.h>
#define Max 1005

long long min(long long a,long long  b)
{
    return a<b?a:b;
}

int main()
{
    int n,t;
    scanf("%d %d",&n,&t);
    long long nums[Max];
    long long sum[Max];
    nums[0]=0;
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&nums[i]);
        sum[i]=sum[i-1]+nums[i];
    }
    long long dp[n+1];
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        dp[i]=dp[i-1]+nums[i]*n*n;
        for(int k=1;k<i;k++)
            if(nums[k]+nums[i]<=t)
                dp[i]=min(dp[i],dp[k-1]+(nums[k]+nums[i])*(sum[i]-sum[k-1]));
    }
    printf("%lld\n",dp[n]);
    return 0;
}
