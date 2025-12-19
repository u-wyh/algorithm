#include<stdio.h>

int main()
{
    long long n,m;
    scanf("%lld %lld",&n,&m);
    long long  nums[n+1],max=0,min=1e9;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&nums[i]);
        max=max>nums[i]?max:nums[i];
        min=min<nums[i]?min:nums[i];
    }
    for(int i=1;i<=m;i++)
    {
        if(max<=2)
            max+=2;
        else
            max*=2;
    }
    printf("%lld\n",max-min);
    return 0;
}
