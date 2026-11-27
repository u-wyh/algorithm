// https://www.luogu.com.cn/problem/P1474
// 题意：有 V 种硬币面值，每种可用任意枚。求正好组成金额 N 的方案数。同一组各面值的枚数固定时，调换放置顺序不算新方案。
// 数据范围：1 ≤ V ≤ 25，1 ≤ N ≤ 10000，答案能用有符号 64 位整数表示。
// 算法标签：背包动态规划

#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    long long dp[m+1];
    for(int i=0;i<=m;i++)
    {
        dp[i]=0;
    }
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=nums[i];j<=m;j++)
        {
            dp[j]+=dp[j-nums[i]];
        }
    }
    printf("%lld\n",dp[m]);
    return 0;
}
