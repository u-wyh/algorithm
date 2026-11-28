// https://www.luogu.com.cn/problem/P1130
// 题意：申请有 N 个步骤、M 个小组。
// 给出每组做每步所需天数。
// 第一步任选组，之后每一步可以留在当前组，或换到下一组，
// 第 M 组的下一组是第 1 组。
// 求做完所有步骤的最少耗时。
// 数据范围：1 ≤ N,M ≤ 2000，每项耗时在 [0,100000]。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划

#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[m+1][n+1];
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }

    int dp[m+1][n+1];
    for(int i=1;i<=m;i++)
        dp[i][1]=nums[i][1];
    dp[0][1]=dp[m][1];
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dp[j][i]=min(dp[j-1][i-1],dp[j][i-1])+nums[j][i];
            if(j==m)
                dp[0][i]=dp[j][i];
        }
    }
    int ans=INT_MAX;
    for(int i=1;i<=m;i++)
    {
        ans=min(ans,dp[i][n]);
    }
    printf("%d\n",ans);
    return 0;
}
