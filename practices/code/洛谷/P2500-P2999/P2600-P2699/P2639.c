// https://www.luogu.com.cn/problem/P2639
// 题意：背包容量 H，有 N 捆干草各自重 S_i（01 背包）。
// 求在总重不超过 H 的前提下最多能装多少公斤干草。
// 输出最大重量。
// 数据范围：5 <= H <= 45000，1 <= N <= 500，
// 1 <= S_i <= H。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划、0-1背包
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int h,n;
    scanf("%d %d",&h,&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[n+1][h+1];
    for(int i=0;i<=h;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=h;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=nums[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-nums[i]]+nums[i]);
        }
    }
    printf("%d\n",dp[n][h]);
    return 0;
}
