// https://www.luogu.com.cn/problem/P2722
// 题意：总时间 m，有 n 类题目（每类可选无限次），
// 第 i 类得分 p_i、耗时 t_i。
// 求规定时间内能获得的最大总分。
// 输出最大总分。
// 数据范围：1 <= n, m <= 10^4，
// 1 <= p_i, t_i <= 10^4。
// 算法标签：完全背包、动态规划
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int cost[n+1],val[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&val[i],&cost[i]);
    }
    int dp[n+1][m+1];
    for(int i=0;i<=m;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k*cost[i]<=j;k++)
            {
                dp[i][j]=max(dp[i][j],dp[i-1][j-cost[i]*k]+k*val[i]);
            }
        }
    }
    printf("%d\n",dp[n][m]);
    return 0;
}
