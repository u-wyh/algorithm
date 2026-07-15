#include<stdio.h>

long long min(long long a,long long b)
{
    return a<b?a:b;
}

long long C(long long  a,long long  b)
{
    if(a==b)
        return 1;
    long long  ans=1;
    for(int i=0;i<min(b,a-b);i++)
    {
        ans*=(a-i);
        ans/=(i+1);
    }
    return ans;
}

long long  fun(long long n,long long  m,long long  k)
{
    if(m==k)
        return 1;
    if(m<k)
        return 0;
    long long ans=0;
    ans+=C(m-1,k);
    n=n-(1<<(m-1));
        m=0;
    while(n>=(1<<m))
        m++;
    //printf("%d\n",m);
    ans+=fun(n,m,k);
    return  ans;
}

int main()
{
    long long  n;
    long long  k;
    scanf("%lld %lld",&n,&k);
    long long  m=0;
    while(n>=(1<<m))
        m++;
    long long ans=0;
    ans+=C(m-1,k);
    n=n-(1<<(m-1));
    m=0;
    while(n>=(1<<m))
        m++;
    //printf("%d\n",m);
    ans+=fun(n,m,k-1);
    printf("%lld\n",ans);
    return 0;
}
