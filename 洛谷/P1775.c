#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int sum[n+1];
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum[i]=sum[i-1]+nums[i];
        //printf("%2d",sum[i]);
    }
    int dp[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=INT_MAX;
            if(i==j)
                dp[i][j]=0;
            if(j==i+1)
                dp[i][j]=nums[j]+nums[i];
        }
    }
    for(int i=n-2;i>=1;i--)
    {
        for(int j=i+2;j<=n;j++)
        {
            for(int m=i;m<j;m++)
                dp[i][j]=min(dp[i][j],dp[i][m]+dp[m+1][j]+sum[j]-sum[i-1]);
        }
    }
    printf("%d\n",dp[1][n]);
    return 0;
}
