#include<stdio.h>

int main()
{
    unsigned long long n,k,p;
    scanf("%llu %llu %llu",&n,&k,&p);
    unsigned long long dp[k+1];

    for(int j=0;j<=k;j++)
    {
        dp[j]=0;
    }

    for(int i=1;i<=n;i++)
    {
        dp[1]=1;
        for(int j=k;j>=2;j--)
        {
            dp[j]=(dp[j-1]%p+((dp[j]%p)*(j%p))%p)%p;
        }
    }
    printf("%llu\n",dp[k]);
    return 0;
}
