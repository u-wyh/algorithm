#include<stdio.h>
#define MOD 19650827

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[n+1][n+1][2];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j][0]=0;
            dp[i][j][1]=0;
            if(i==j)
                dp[i][j][0]=1;
        }
    }
    for(int len=2;len<=n;len++)
    {
        for(int i=1;i<=n-len+1;i++)
        {
            int j=len+i-1;
            if (nums[i] < nums[i + 1]) {
                dp[i][j][0] = (dp[i][j][0] + dp[i + 1][j][0]) % MOD;
            }
            if (nums[i] < nums[j]) {
                dp[i][j][0] = (dp[i][j][0] + dp[i + 1][j][1]) % MOD;
            }
            if (nums[j] > nums[i]) {
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][0]) % MOD;
            }
            if (nums[j] > nums[j - 1]) {
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][1]) % MOD;
            }
        }
    }
    printf("%d\n", (dp[1][n][0] + dp[1][n][1]) % MOD);
    return 0;
}
