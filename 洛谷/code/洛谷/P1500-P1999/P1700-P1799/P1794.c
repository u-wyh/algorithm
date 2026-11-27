// https://www.luogu.com.cn/problem/P1794
// 题意：给定体积上限 V、重量上限 G 以及 N 件装备的火力、体积和重量。
// 每件最多选一次，在两项总开销均不超限时求最大总火力。
// 数据范围：1 ≤ V,G,N ≤ 500，
// 1 ≤ T_i,V_i,G_i ≤ 10^9。
// 算法标签：二维费用背包、0-1背包、动态规划

#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int V,G,n;
    scanf("%d %d %d",&V,&G,&n);
    int v[n+1],g[n+1],val[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&val[i],&v[i],&g[i]);
    }
    int dp[V+1][G+1];
    for(int i=0;i<=V;i++)
    {
        for(int j=0;j<=G;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=V;j>=0;j--)
        {
            for(int k=G;k>=0;k--)
            {
                if(j>=v[i]&&k>=g[i])
                    dp[j][k]=max(dp[j][k],dp[j-v[i]][k-g[i]]+val[i]);
            }
        }
    }
    printf("%d\n",dp[V][G]);
    return 0;
}
