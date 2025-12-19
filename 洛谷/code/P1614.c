#include<stdio.h>

long long min(long long  a,long long  b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    long long sum[n+1],ans=1e9;
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum[i]=sum[i-1]+nums[i];
    }
    for(int i=m;i<=n;i++)
    {
        ans=min(ans,sum[i]-sum[i-m]);
    }
    printf("%lld\n",ans);
    return 0;
}
