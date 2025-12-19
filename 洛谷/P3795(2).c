#include<stdio.h>
#define mod 14233333
int main()
{
    int n;
    scanf("%d",&n);
    long long a=1;
    long long b=1;
    long long c;
    for(int i=2;i<=n;i++)
    {
        c=(b+a*(i-1)%mod)%mod;
        a=b;
        b=c;
    }
    printf("%lld\n",c);
    return 0;
}
