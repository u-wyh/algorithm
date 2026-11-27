// https://www.luogu.com.cn/problem/P1616
// 题意：输入总采药时间 t 和草药种类数 m，
// 及每种草药的采摘时间 a_i 与价值 b_i。
// 每种草药可无限次采摘（完全背包），输出总时间不超过 t 时能获得的最大价值。
// 数据范围：
// 1 <= m <= 10^4（草药种类数）
// 1 <= t <= 10^7（总时间）
// 1 <= m*t <= 10^7
// 1 <= a_i, b_i <= 10^4（每种草药耗时与价值）
// 算法标签：完全背包、动态规划
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    long long t,n;
    scanf("%lld %lld",&t,&n);
    int cost[n+1],val[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%lld %lld",&cost[i],&val[i]);
    }
    long long dp[n+1][t+1];
    for(int i=0;i<=t;i++)
        dp[0][i]=0;
    for(int i=0;i<=n;i++)
        dp[i][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=t;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k*cost[i]<=j;k++)
                dp[i][j]=max(dp[i][j],dp[i-1][j-k*cost[i]]+k*val[i]);
        }
    }
    printf("%lld\n",dp[n][t]);
    return 0;
}
