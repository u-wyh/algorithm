// https://www.luogu.com.cn/problem/P2028
// 题意：把 n 个互不相同的苹果分进 k 个不区分顺序的篮子，每个篮子都不能为空。输出分法数对 p 取模的值。
// 数据范围：n ≤ 10000，k ≤ 1000，n ≥ k，输出值可用 64 位整数表示。

#include<stdio.h>

int main()
{
    unsigned long long n,k,p;
    scanf("%llu %llu %llu",&n,&k,&p);
    unsigned long long dp[k+1];

    for(int j=0;j<=k;j++)
    {
        dp[j]=0;
    }

    for(int i=1;i<=n;i++)
    {
        dp[1]=1;
        for(int j=k;j>=2;j--)
        {
            dp[j]=(dp[j-1]%p+((dp[j]%p)*(j%p))%p)%p;
        }
    }
    printf("%llu\n",dp[k]);
    return 0;
}
