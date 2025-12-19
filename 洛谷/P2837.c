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
    int dp[n+1][2];
    dp[1][nums[1]-1]=0;
    dp[1][2-nums[1]]=1;
    for (int i=2;i<=n;++i){
        if (nums[i]==1){
            dp[i][0]=dp[i-1][0];
            dp[i][1]=min(dp[i-1][1],dp[i-1][0])+1;
        }else{
            dp[i][0]=dp[i-1][0]+1;
            dp[i][1]=min(dp[i-1][1],dp[i-1][0]);
        }
    }
    printf("%d\n",min(dp[n][0],dp[n][1]));
    return 0;
}
