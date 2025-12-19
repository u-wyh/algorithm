#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,beginLevel,maxLevel;
    scanf("%d %d %d",&n,&beginLevel,&maxLevel);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[n+1][maxLevel+1];
    for(int i=0;i<=maxLevel;i++)
        dp[0][i]=0;
    dp[0][beginLevel]=1;
    for(int i=1;i<=n;i++)
    {
        for (int j = maxLevel; j >= 0; j--) {
            dp[i][j] = 0; // 初始化当前位置为false
            if (j - nums[i] >= 0 && dp[i-1][j-nums[i]] != 0) {
                dp[i][j] = 1; // 如果可以向下走，则更新状态
            }
            if (j + nums[i] <= maxLevel && dp[i-1][j+nums[i]] != 0) {
                dp[i][j] = 1; // 如果可以向上走，则更新状态
            }
        }
    }
    for (int i = maxLevel; i >= 1; i--) {
        if (dp[n][i] == 1) {
            printf("%d", i);
            return 0;
        }
    }

    printf("-1");
    return 0;
}
