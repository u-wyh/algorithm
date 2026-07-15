#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[361];
    for(int i=0;i<=360;i++)
        dp[i]=0;
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=360;j++)
        {
            if(j>=nums[i])
                dp[j]|=dp[j-nums[i]];
            else
                dp[j]|=dp[(j+nums[i])%360];
        }
    }
    int nums2[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&nums2[i]);
        if(dp[nums2[i]])
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
