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
    int dp[n+1][m+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=0;
            if(j==0)
                dp[i][j]=1;
        }
    }
    //dp[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k*nums[i]<=j;k++)
            {
                dp[i][j]=(dp[i][j]%mod+dp[i-1][j-k*nums[i]]%mod)%mod;
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        printf("%d\n",dp[n][i]);
    }
    return 0;
}
