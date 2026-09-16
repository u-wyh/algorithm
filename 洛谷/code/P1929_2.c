#include<stdio.h>
#include<limits.h>
#include<math.h>

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
    int dp[n+1];
    for(int i=1;i<=n;i++)
    {
        dp[i]=INT_MAX;
    }
    dp[1]=0;
    for(int i=2;i<=n;i++)
    {
        if(nums[i]==nums[i-1]+1)
            dp[i]=min(dp[i],dp[i-1]+1);
        for(int j=i-1;j>0;j--)
        {
            for(int k = j - 1; k > 0; k--) {
                if((pow(2,k) + nums[j-k]) >= nums[i]) {
                    dp[i] = min(dp[i], dp[j] +k+ 1);
                }
            }
        }
    }
    if(dp[n]>=INT_MAX)
        printf("-1\n");
    else
        printf("%d\n",dp[n]);
    return 0;
}
