// https://www.luogu.com.cn/problem/P8725
// 题意：输入 D, T, M；
// 初始距下游峡谷 D 米，共 T 秒，
// 每秒可选择消耗 1 点体力向上游前进 1m 或不消耗体力向下游移动 1m；
// 要求在任一时刻向下游总位移始终严格小于 D（否则失败），
// 且在 T 秒内恰好花光 M 点体力，
// 输出可获救的总方案数对 10^9+7 取模的结果。
// 数据范围：1 <= T <= 3000，1 <= D <= T，
// 1 <= M <= 1500。
// 算法标签：动态规划
#include<stdio.h>

#define mod 1000000007

int main()
{
    int d,t,m;
    scanf("%d %d %d",&d,&t,&m);
    if(d+2*m-t<=0||m>t)
    {
        int ans=0;
        printf("%d",ans);
        return 0;
    }
    int dp[t+1][d+m+2];
    for(int i=0;i<=t;i++)
    {
        for(int j=0;j<=d+m+1;j++)
        {
            if(i==0||j==0||j==d+m+1)
                dp[i][j]=0;
        }
    }
    dp[0][d]=1;
    for(int i=1;i<=t;i++)
    {
        for(int j=1;j<=d+m;j++)
        {
            dp[i][j]=(dp[i-1][j-1]%mod+dp[i-1][j+1]%mod)%mod;
        }
    }
    printf("%d\n",dp[t][d+2*m-t]);
    return 0;
}
