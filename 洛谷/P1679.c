#include<stdio.h>
#include<math.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[19];
    for(int i=1;i<=18;i++)
    {
        nums[i]=pow(i,4);
        //printf("%7d",nums[i]);
    }
    int dp[19][n+1];
    for(int i=1;i<=18;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=INT_MAX;
        }
    }
    dp[1][1]=1;
    for(int i=2;i<=18;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=nums[i])
                dp[i][j]=min(dp[i][j],dp[i-1][j-nums[i]]+1);
        }
    }
    printf("%d\n",dp[18][n]);
    return 0;
}
