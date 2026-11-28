// https://www.luogu.com.cn/problem/P3399
// 题意：输入城市段数 N、总天数上限 M，各段距离 D_1..D_N，
// 以及第 1..M 天的天气恶劣值 C_1..C_M。
// 从 0 号城市出发，
// 每天可休息（疲劳 0）或从 i-1 走到 i（疲劳 D_i * C_j），
// 要求在不超过 M 天内到达 N 号城市。
// 输出最小总疲劳度。
// 数据范围：1 <= N <= M <= 1000，
// 1 <= D_i, C_i <= 1000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划
#include<stdio.h>
#include<limits.h>
#include<string.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&b[i]);
    }
    int dp[n+1][m+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=INT_MAX;
        }
    }
    for(int i=0;i<=m;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=m;j++)
        {
            //dp[i][j]=min(dp[i][j],dp[i-1][j]);
            dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+a[i]*b[j]);
        }
    }
    int ans=INT_MAX;
    for(int i=n;i<=m;i++)
        ans=min(ans,dp[n][i]);
    printf("%d\n",ans);
    return 0;
}
