// https://www.luogu.com.cn/problem/P2193
// 题意：求长度为 p、所有元素为不超过 n 的正整数
// 且后一项能被前一项整除的序列个数。
// 输出方案数对 10^9+7 取模的结果。
// 数据范围：1 <= n, p <= 2*10^3。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划、数论
#include<stdio.h>
#define mod 1000000007

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int dp[k+1][n+1];
    for(int i=0;i<=k;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        dp[1][i]=1;
    }
    for(int i=2;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int m=1;m<=n/j;m++)
                dp[i][m*j]=(dp[i][m*j]+dp[i-1][j])%mod;
        }
    }
    int ans=dp[k][1];
    for(int i=2;i<=n;i++)
        ans=(ans+dp[k][i])%mod;
    printf("%d\n",ans);
    return 0;
}
