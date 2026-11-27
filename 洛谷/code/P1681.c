// https://www.luogu.com.cn/problem/P1681
// 题意：给定 N 行 M 列的黑白格子，找一个正方形，使内部任意两个共边的格子颜色不同。输出最大的边长。
// 数据范围：1 ≤ N,M ≤ 1500，每个格子为 0 或 1。
// 算法标签：动态规划

#include<stdio.h>

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
    int n ,m;
    scanf("%d %d",&n,&m);
    int nums[n+1][m+1];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    int dp[n+1][m+1];
    int ans=0;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=1;
        }
    }
    for(int i=2;i<=n;i++)
    {
        for(int j=2;j<=m;j++)
        {
            if(nums[i][j]==nums[i-1][j-1]&&
               nums[i][j]!=nums[i][j-1]&&
               nums[i][j]!=nums[i-1][j])
            {
                dp[i][j]=min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1])+1;
            }
            ans=max(ans,dp[i][j]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
