#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    unsigned long long  dp[n+1];
    for(int i=1;i<=n;i++)
    {
        dp[i]=0;
    }
    dp[0]=1;
    for(int i=1;i<=m;i++)
    {
        for(int j=i;j<=n;j++)
        {
            //for(int k=1;k*i<=j;k++)
                //dp[j]+=dp[j-i*k];
                dp[j]+=dp[j-i];
        }
    }
    printf("%llu\n",dp[n]);
    return 0;
}
