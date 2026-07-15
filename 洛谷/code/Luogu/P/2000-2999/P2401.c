#include<stdio.h>
#define mod 2015

int dp[1005][1005];

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    dp[2][0]=1;
    dp[2][1]=1;
    for(int i=2;i<=n-1;i++)
    {
        for(int j=0;j<=i-1;j++)
        {
            dp[i+1][j]=(dp[i][j]*(j+1)%mod+dp[i+1][j]%mod)%mod;
            dp[i+1][j+1]=(dp[i][j]*(i-j)%mod+dp[i+1][j+1]%mod)%mod;
        }
    }
    printf("%d\n",dp[n][k]);
    return 0;
}
