#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int h,n;
    scanf("%d %d",&h,&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[n+1][h+1];
    for(int i=0;i<=h;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=h;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=nums[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-nums[i]]+nums[i]);
        }
    }
    printf("%d\n",dp[n][h]);
    return 0;
}
