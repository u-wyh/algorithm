// https://www.luogu.com.cn/problem/P1802
// 题意：有 n 个游戏对手和 x 个道具。
// 对第 i 人花至少 use_i 个道具可获胜并得到 win_i 经验，
// 否则得到 lose_i 经验。
// 安排道具使总经验最大，输出其五倍。
// 数据范围：0 ≤ n,x ≤ 1000，
// 0 < lose_i ≤ win_i ≤ 10^6，
// 0 ≤ use_i ≤ 1000。
// 算法标签：0-1背包、动态规划

#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}
;
int main()
{
    int n,x;
    scanf("%d %d",&n,&x);
    int lose[n+1],win[n+1],use[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&lose[i],&win[i],&use[i]);
    }
    long long  dp[n+1][x+1];
    for(int i=0;i<=x;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=x;j++)
        {
            dp[i][j]=dp[i-1][j]+lose[i];
            if(j>=use[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-use[i]]+win[i]);
        }
    }
    printf("%lld\n",5*dp[n][x]);
    return 0;
}
