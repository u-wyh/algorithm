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
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    long long  dp[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int l=0;l<n;l++)
    {
        long long ans=INT_MAX;
        if(l==0)
            ans=0;
        else
            for(int i=1;i+l<=n;i++)
            {
                int j=i+l;
                dp[i][j]=dp[i+1][j-1]+abs(nums[j]-nums[i]);
                ans=min(dp[i][j],ans);
            }
        printf("%d ",ans);
    }
    return 0;
}
