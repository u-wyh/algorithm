#include<stdio.h>

long long  C(int n)
{
    long long  ans=1;
    for(int i=1;i<=n;i++)
        ans=ans*(2*n-i+1)/i;
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%lld\n",C(n)/(n+1));
    return 0;
}
