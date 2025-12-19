#include<stdio.h>

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
    for(int i=0;i<=n;i++)
    {
        dp[i][0]=0;
        dp[i][1]=0;
    }
    dp[1][0]=1;
    dp[1][1]=1;
    for(int i=2;i<=n;i++)
    {
        if(nums[i]>nums[i-1])
            dp[i][0]=dp[i-1][1]+1;
        else
            dp[i][0]=dp[i-1][0];
        if(nums[i]<nums[i-1])
            dp[i][1]=dp[i-1][0]+1;
        else
            dp[i][1]=dp[i-1][1];
    }
    printf("%d\n",dp[n][0]>dp[n][1]?dp[n][0]:dp[n][1]);
    return 0;
}
/*
代码中dp[i][0]是指以第i个数字作为  升高  结尾最长可以有几个
      dp[i][1]是指以第i个数字作为  降低  结尾最长可以有几个
状态转移是 if(nums[i]>nums[i-1])
           {
                dp[i][0]=dp[i-1][1]+1;
                dp[i][1]=dp[i-1][1];
           }
           如果这个数字大于前面的那个数字
           那么以他结尾的上升长度是以前面一个数字下降结尾长度加上1
           那么以他结尾的下降长度是前面一个数字下降结尾长度（此时不是以当前数字结尾）
            if(nums[i]<nums[i-1])
           {
                dp[i][1]=dp[i-1][0]+1;
                dp[i][0]=dp[i-1][0];
           }
           如果这个数字小于前面的那个数字
           那么以他结尾的上升长度是前面一个数字上升结尾长度（此时不是以当前数字结尾）
           那么以他结尾的下降长度是以前面一个数字上升结尾长度加上1
*/
