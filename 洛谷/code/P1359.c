// https://www.luogu.com.cn/problem/P1359
// 题意：n 个出租站沿江从上游到下游编号。从 i 租船到下游 j 还船的价格为 r[i][j]，途中可在任意站换船。求从 1 号站到 n 号站的最低总租金。
// 数据范围：1 ≤ n ≤ 200，计算过程中所有数值至多 10^6。

#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n][n];
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    int dp[n];
    for(int i=0;i<n;i++)
        dp[i]=INT_MAX;
    dp[n-1]=0;
    for(int i=n-2;i>=0;i--)
    {
        for(int j=i+1;j<n;j++)
        {
            dp[i]=min(dp[i],dp[j]+nums[i][j]);
        }
    }
    printf("%d\n",dp[0]);
    return 0;
}
