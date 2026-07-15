#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    long long  nums[n+1],k1=INT_MAX,k2=INT_MIN;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&nums[i]);
        k1=min(k1,nums[i]);
        k2=max(k2,nums[i]);
    }
    printf("%lld\n",k2-k1);
    return 0;
}
