#include<stdio.h>
#define p 10000000

int main()
{
    int n,f;
    scanf("%d %d",&n,&f);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        nums[i]%=f;
    }
    int dp[n+1][f];
    for(int i=0;i<=n;i++)
        for(int j=0;j<f;j++)
            dp[i][j]=0;
    for(int i=1;i<=n;i++)
        dp[i][nums[i]]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<f;j++)
        {
            dp[i][j]=((dp[i][j]+dp[i-1][j])%p+dp[i-1][(j-nums[i]+f)%f])%p;
        }
    }
    printf("%d\n",dp[n][0]);
    return 0;
}
