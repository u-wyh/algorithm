// https://www.luogu.com.cn/problem/P2401
// 题意：将 1 到 n 排列，相邻两数间根据大小填入 < 或 >。
// 求恰好有 k 个 < 号的排列个数。
// 输出方案数对 2015 取模的结果。
// 数据范围：0 <= k < n <= 1000。
// 难度评分：1500（洛谷分级换算）
// 算法标签：动态规划
#include<stdio.h>
#define mod 2015

int dp[1005][1005];

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    dp[2][0]=1;
    dp[2][1]=1;
    for(int i=2;i<=n-1;i++)
    {
        for(int j=0;j<=i-1;j++)
        {
            dp[i+1][j]=(dp[i][j]*(j+1)%mod+dp[i+1][j]%mod)%mod;
            dp[i+1][j+1]=(dp[i][j]*(i-j)%mod+dp[i+1][j+1]%mod)%mod;
        }
    }
    printf("%d\n",dp[n][k]);
    return 0;
}
