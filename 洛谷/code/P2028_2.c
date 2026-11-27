// https://www.luogu.com.cn/problem/P2028
// 题意：把 n 个互不相同的苹果分进 k 个不区分顺序的篮子，每个篮子都不能为空。输出分法数对 p 取模的值。
// 数据范围：n ≤ 10000，k ≤ 1000，n ≥ k，输出值可用 64 位整数表示。
// 算法标签：动态规划、组合数学

#include<stdio.h>

int main()
{
    unsigned long long n,k,p;
    scanf("%llu %llu %llu",&n,&k,&p);
    unsigned long long dp[n+1][k+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=k;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        dp[i][1]=1;
        for(int j=2;j<=k;j++)
        {
            dp[i][j]=(dp[i-1][j-1]%p+(dp[i-1][j]%p)*(j%p))%p;
        }
    }
    printf("%llu\n",dp[n][k]);
    return 0;
}
