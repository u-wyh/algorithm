// https://www.luogu.com.cn/problem/P2871
// 题意：N 件物品（重量 W_i，价值 D_i），背包容量 M（01 背包）。
// 求背包能装下的最大总价值。
// 输出最大总价值。
// 数据范围：1 <= N <= 3402，1 <= M <= 12880，
// 1 <= W_i <= 400，1 <= D_i <= 100。
// 算法标签：动态规划、0-1背包
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int cost[n+1],val[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&cost[i],&val[i]);
    }
    int dp[n+1][m+1];
    for(int i=0;i<=m;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=cost[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-cost[i]]+val[i]);
        }
    }
    printf("%d\n",dp[n][m]);
    return 0;
}
