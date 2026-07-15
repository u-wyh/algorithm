#include<stdio.h>

long long min(long long a,long long b)
{
    return a<b?a:b;
}

long long max(long long a,long long b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    long long nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&nums[i]);
    }
    long long ans=1e9;
    for(int i=2;i<=n;i++)
    {
        ans=min(ans,max(nums[i],nums[i-1])-min(nums[i],nums[i-1]));
    }
    printf("%lld\n",ans);
    return 0;
}
