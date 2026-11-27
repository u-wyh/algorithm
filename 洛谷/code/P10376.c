// https://www.luogu.com.cn/problem/P10376
// 题意：拿一个初值为 n 的数，每轮选择减 a 或减 b，第一次变成不大于 c 时立刻停。
// 求不同操作序列的个数，对 10^9+7 取模。
// a 等于 b 时两种操作也要区分。
// 数据范围：1 ≤ a,b,c ≤ n ≤ 2 × 10^5。
// 算法标签：动态规划

#include<stdio.h>
#define mod 1000000007

long long dp[200005];

int main()
{
    int n,a,b,c;
    scanf("%d %d %d %d",&n,&a,&b,&c);
    for(int i=0;i<200005;i++)
        dp[i]=0;
    dp[n]=1;
    for(int i=n-1;i>=0;i--)
    {
        if(i+a<=n&&i+a>c)
            dp[i]=(dp[i]+dp[i+a])%mod;
        if(i+b<=n&&i+b>c)
            dp[i]=(dp[i]+dp[i+b])%mod;
    }
    long long ans=0;
    for(int i=0;i<=c;i++)
    {
        ans=(ans+dp[i])%mod;
    }
    printf("%lld\n",ans);
    return 0;
}
