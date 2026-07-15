#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int num[182];
    for(int i=0;i<=181;i++)
        num[i]=i*i;
    int dp[32769][5];
    for(int i=0;i<=32768;i++)
    {
        for(int j=0;j<=4;j++)
        {
            dp[i][j]=0;
        }
    }
    dp[0][0]=1;
    for(int i=1;i<=181;i++)
    {
        for(int j=num[i];j<=32768;j++)
        {
            for(int k=1;k<=4;k++)
            {
                dp[j][k]+=dp[j-num[i]][k-1];
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        long long ans=0;
        ans=(dp[nums[i]][1]+dp[nums[i]][2]+dp[nums[i]][3]+dp[nums[i]][4]);
        printf("%lld\n",ans);
    }
    return 0;
}
