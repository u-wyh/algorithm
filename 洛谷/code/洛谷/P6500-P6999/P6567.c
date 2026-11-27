// https://www.luogu.com.cn/problem/P6567
// 题意：n 种钱币，第 i 种面额 k_i 元共 a_i 张；
// m 块手表价格为 t_i 元。
// 不找零前提下，判断每块手表能否恰好凑出（输出 Yes / No）。
// 数据范围：1 <= n <= 200，1 <= m <= 10^5，
// 1 <= a_i <= 1000，1 <= k_i <= 500000
// 0 <= t_i <= 500000。
// 算法标签：多重背包、动态规划
#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[n+1];
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        sum+=a[i]*b[i];
    }
    int dp[sum+1];
    for(int j=0;j<=sum;j++)
    {
        dp[j]=0;
        if(j==0)
            dp[j]=1;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=sum;j>=1;j--)
        {
            for(int k=1;k<=b[i]&&j>=k*a[i];k++)
            {
                dp[j]|=dp[j-k*a[i]];
            }
        }
    }
    int nums;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&nums);
        if(dp[nums])
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
