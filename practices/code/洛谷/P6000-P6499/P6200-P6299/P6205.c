// https://www.luogu.com.cn/problem/P6205
// 题意：商场有价格为 1, 2, ..., K 元的 K 种工具（每种无限），
// 手里有 N 元必须恰好花完，求不同的无序购买方案数（需高精度）。
// 数据范围：1 <= K <= 100，1 <= N <= 1000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：完全背包、动态规划
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    unsigned long long  dp[n+1];
    for(int i=1;i<=n;i++)
    {
        dp[i]=0;
    }
    dp[0]=1;
    for(int i=1;i<=m;i++)
    {
        for(int j=i;j<=n;j++)
        {
            //for(int k=1;k*i<=j;k++)
                //dp[j]+=dp[j-i*k];
                dp[j]+=dp[j-i];
        }
    }
    printf("%llu\n",dp[n]);
    return 0;
}
