#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int ans=0;
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        ans=max(ans,nums[i]);
    }
    int dp[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        dp[i][i]=nums[i];
    }
    for(int len=2;len<=n;len++)
    {
        for(int i=1;i<=n-len+1;i++)
        {
            int j=i+len-1;
            for(int k=i;k<j;k++)
            {
                if(dp[i][k]==dp[k+1][j])
                {
                    dp[i][j] = max(dp[i][j], dp[i][k] + 1);
                    ans = max(ans, dp[i][j]);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
