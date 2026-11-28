// https://www.luogu.com.cn/problem/P2946
// 题意：输入奶牛数 N、幸运数字 F，以及每头奶牛的能力值 R_i。
// 从这 N 头奶牛中选出至少 1 头组成一支队伍，
// 要求所有队员的能力值总和恰好是 F 的倍数。
// 统计满足要求的非空队伍组合方案数。
// 输出一个整数，表示方案数对 10^8 取模的值。
// 数据范围：对于 100% 的数据，1 <= N <= 2000，
// 1 <= F <= 1000，1 <= R_i <= 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划、背包动态规划
#include<stdio.h>
#define p 10000000

int main()
{
    int n,f;
    scanf("%d %d",&n,&f);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        nums[i]%=f;
    }
    int dp[n+1][f];
    for(int i=0;i<=n;i++)
        for(int j=0;j<f;j++)
            dp[i][j]=0;
    for(int i=1;i<=n;i++)
        dp[i][nums[i]]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<f;j++)
        {
            dp[i][j]=((dp[i][j]+dp[i-1][j])%p+dp[i-1][(j-nums[i]+f)%f])%p;
        }
    }
    printf("%d\n",dp[n][0]);
    return 0;
}
