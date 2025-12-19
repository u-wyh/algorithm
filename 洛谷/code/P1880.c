#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[2*n+1];
    int sum[2*n+1];
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        nums[n+i]=nums[i];
        sum[i]=sum[i-1]+nums[i];
        //printf("%2d",sum[i]);
    }
    for(int i=n+1;i<=2*n;i++)
        sum[i]=sum[i-1]+nums[i];
    int dp[2*n+1][2*n+1];
    int dp2[2*n+1][2*n+1];
    for(int i=0;i<=2*n;i++)
    {
        for(int j=0;j<=2*n;j++)
        {
            dp[i][j]=INT_MAX;
            dp2[i][j]=INT_MIN;
            if(i==j)
            {
                dp[i][j]=0;
                dp2[i][j]=0;
            }
            if(j==i+1)
            {
                dp[i][j]=nums[j]+nums[i];
                dp2[i][j]=nums[j]+nums[i];
            }
        }
    }
    for(int i=2*n-2;i>=1;i--)
    {
        for(int j=i+2;j<=2*n&&j<i+n;j++)
        {
            for(int m=i;m<j;m++)
            {
                dp[i][j]=min(dp[i][j],dp[i][m]+dp[m+1][j]+sum[j]-sum[i-1]);
                dp2[i][j]=max(dp2[i][j],dp2[i][m]+dp2[m+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++)
        ans=min(ans,dp[i][i+n-1]);
    int ans2=INT_MIN;
    for(int i=1;i<=n;i++)
        ans2=max(ans2,dp2[i][i+n-1]);
    printf("%d\n",ans);
    printf("%d\n",ans2);
    return 0;
}
