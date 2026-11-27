// https://www.luogu.com.cn/problem/P4389
// 题意：n 种体积为 v_i 的商品（每种无限件），给定 m，对每个 s in [1, m] 求恰好装满体积 s 的方案数（对 998244353 取模）。
// 数据范围：1 <= n, m <= 10^5，1 <= v_i <= m。
#include<stdio.h>
#define mod 998244353
// 算法标签：动态规划、完全背包

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[m+1];
    for(int i=0;i<=m;i++)
    {
        dp[i]=0;
    }
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=nums[i];j--)
        {
            for(int k=1;k*nums[i]<=j;k++)
            {
                dp[j]=(dp[j]+dp[j-k*nums[i]])%mod;
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        printf("%d\n",dp[i]);
    }
    return 0;
}

