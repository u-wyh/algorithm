// https://www.luogu.com.cn/problem/P1508
// 题意：给 m 行 n 列的能量格。
// 人从末行正中下方开始，每次向上一行的正前、左前或右前移动，所经格子能量必须计入。
// 求到达最上边时能获得的最大总能量。
// 数据范围：m,n ≤ 200，列数 n 为奇数，
// 格子是绝对值不超过 10^5 的整数。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划

#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int nums[m+2][n+1];
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    for(int i=0;i<=n;i++)
        nums[m+1][i]=0;
    int dp[m+2][n+2];
    for(int i=0;i<=m+1;i++)
    {
        for(int j=0;j<=n+1;j++)
        {
            dp[i][j]=INT_MIN/2;
        }
    }
    dp[m+1][(n+1)/2]=nums[m+1][(n+1)/2];
    for(int i=m;i>=1;i--)
    {
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=max(max(dp[i+1][j],dp[i+1][j+1]),dp[i+1][j-1])+nums[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[1][i]);
    printf("%d\n",ans);
    return 0;
}
