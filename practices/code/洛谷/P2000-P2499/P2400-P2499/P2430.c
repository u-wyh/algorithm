// https://www.luogu.com.cn/problem/P2430
// 题意：m 道题属于 n 个知识点，给出第 i 个知识点基准耗时及两人的水平值比。
// 每道题有对应奖励值 q，求在规定时间内能获得的最大奖励总和。
// 输出最大奖励值。
// 数据范围：1 <= n, m <= 100，规定时间 <= 5000，
// 1 <= q <= 1000，|水平值| <= 10^9。
// 算法标签：0-1背包、动态规划
#include<stdio.h>

int  max(int  a,int  b)
{
    return a>b?a:b;
}

int main()
{
    int x1,x2,k;
    scanf("%d %d",&x1,&x2);
    k=x2/x1;
    int n,m;
    scanf("%d %d",&n,&m);
    int t2[m+1],t1[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&t2[i]);
        t1[i]=(t2[i]*k);
    }
    int cost[n+1],val[n+1];
    int p[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&p[i],&val[i]);
        cost[i]=t1[p[i]];
    }
    int t;
    scanf("%d",&t);
    int dp[n+1][t+1];
    for(int i=0;i<=t;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=t;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=cost[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-cost[i]]+val[i]);
        }
    }
    printf("%d\n",dp[n][t]);
    return 0;
}
