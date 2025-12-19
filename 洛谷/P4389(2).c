#include<stdio.h>
#define mod 998244353

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[m+1];
    for(int i=0;i<=m;i++)
    {
        dp[i]=0;
    }
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=nums[i];j--)
        {
            for(int k=1;k*nums[i]<=j;k++)
            {
                dp[j]=(dp[j]+dp[j-k*nums[i]])%mod;
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        printf("%d\n",dp[i]);
    }
    return 0;
}

