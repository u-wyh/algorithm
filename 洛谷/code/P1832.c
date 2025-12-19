#include<stdio.h>
#include<math.h>
#define Max 1001

int isprime(int n)
{
    for(int i=2;i*i<=n;i++)
        if(n%i==0)
            return 0;
    return 1;
}

int main()
{
    int su[Max];
    int num=0;
    for(int i=2;i<=1000;i++)
    {
        if(isprime(i))
            {
                su[++num]=i;
                //printf("%5d",su[num]);
            }
    }
    int n;
    scanf("%d",&n);
    long long dp[n+1];
    for(int i=0;i<=n;i++)
        dp[i]=0;
    dp[0]=1;
    for(int i=1;i<=num;i++)
    {
        for(int j=su[i];j<=n;j++)
        {
            dp[j]+=dp[j-su[i]];
        }
    }
    printf("%lld\n",dp[n]);
    return 0;
}
