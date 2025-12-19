#include<stdio.h>


int min(int a,int b)
{
    return a<b?a:b;
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
    int dp[n+1][3];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<3;j++)
        {
            dp[i][j]=1e9;
        }
    }
    dp[1][nums[1]+1]=0;
    for(int i=2;i<=n;i++)
    {
        if(nums[i]==-1)
        {
            dp[i][0]=dp[i-1][0];
            dp[i][2]=dp[i-1][2]+2;
        }
        if(nums[i]==0)
        {
            dp[i][0]=dp[i-1][0]+1;
            dp[i][1]=min(dp[i-1][1],dp[i-1][0]);
            dp[i][2]=dp[i-1][2]+1;
        }
        if(nums[i]==1)
        {
            dp[i][0]=dp[i-1][0]+2;
            dp[i][1]=dp[i-1][0]+1;
            dp[i][2]=min(dp[i-1][2],min(dp[i-1][0],dp[i-1][1]));
        }
    }
    int ans=min(dp[n][0],min(dp[n][1],dp[n][2]));
    if(ans>=1e9)
        printf("BRAK\n");
    else
        printf("%d\n",ans);
    return 0;
}
