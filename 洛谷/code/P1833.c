// https://www.luogu.com.cn/problem/P1833
// 题意：给定开始和结束时间及 n 棵树。
// 赏第 i 棵树一次耗时 T_i，得到 C_i 美学值，最多赏 P_i 次，P_i=0 表示不限次数。
// 求在总时间以内能得到的最大美学值。
// 数据范围：n ≤ 10000，时间同一天，间隔至多 1000 分钟。1 ≤ T_i ≤ 150，1 ≤ C_i ≤ 200，0 ≤ P_i ≤ 100。
// 算法标签：混合背包、动态规划

#include<stdio.h>

typedef struct time
{
    int hh;
    int mm;
}T;

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    T s[2];
    for(int i=0;i<2;i++)
    {
        scanf("%d:%d",&s[i].hh,&s[i].mm);
    }
    int times=(s[1].hh-s[0].hh)*60+s[1].mm-s[0].mm;
    //printf("%d\n",times);
    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1],c[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
        if(c[i]==0)
            c[i]=1e7;
    }
    int dp[times+1];
    for(int j=0;j<=times;j++)
        dp[j]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=times;j>=a[i];j--)
        {
            for(int k=1;k<=c[i]&&k*a[i]<=j;k++)
                dp[j]=max(dp[j],dp[j-k*a[i]]+k*b[i]);
        }
    }
    int ans=0;
    for(int j=1;j<=times;j++)
    {
        ans=max(ans,dp[j]);
    }
    printf("%d\n",ans);
    return 0;
}
