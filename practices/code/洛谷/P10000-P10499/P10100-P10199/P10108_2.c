// https://www.luogu.com.cn/problem/P10108
// 题意：游戏有 N 关，从第 0 关开始。
// 每次任选 M 个通道之一向前跳 a[i] 关，同时拿到离开这一关的分数 b。
// 跳到编号至少为 N 就结束，求最高总分。
// 数据范围：1 ≤ N ≤ 10^4，1 ≤ M ≤ 100，
// 1 ≤ a[i] ≤ N，-10^5 ≤ b[i] ≤ 10^5。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划

#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int choice[m+1];
    int Max=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&choice[i]);
        Max=max(Max,choice[i]);
    }
    int val[n+Max+1];
    val[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&val[i]);
    }
    for(int i=n+1;i<=n+Max;i++)
        val[i]=0;
    int dp[Max+n+1];
    for(int i=0;i<=Max+n;i++)
        dp[i]=INT_MIN;
    dp[1]=val[1];
    for(int j=2;j<=Max+n;j++)
    {
        for(int i=1;i<=m;i++)
        {
            if(j>=choice[i])
                dp[j]=max(dp[j],dp[j-choice[i]]+val[j]);
        }
    }
    //for(int i=1;i<=n+Max;i++)
      //  printf("%d\n",dp[i]);
    int ans=0;
    for(int i=n;i<=Max+n;i++)
    {
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}

