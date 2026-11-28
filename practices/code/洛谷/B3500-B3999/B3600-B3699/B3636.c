// https://www.luogu.com.cn/problem/B3636
// 题意：文档起初只有一个字，目标获得恰好 n 个字。
// 每次可以添加一个字，或复制粘贴整篇使字数翻倍。
// 输出：达到目标所需的最少操作次数。
// 数据范围：n 为正整数，n <= 10^6。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划
#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int dp[n+1];
    dp[1]=0;
    for(int i=2;i<=n;i++)
    {
        dp[i]=dp[i-1]+1;
        if(i%2==0)
            dp[i]=min(dp[i],dp[i/2]+1);
    }
    printf("%d\n",dp[n]);
    return 0;
}
