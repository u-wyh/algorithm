// https://www.luogu.com.cn/problem/P1968
// 题意：从 100 美元开始，给定 N 天的双向汇率，
// 第 i 天 100 美元可与 A_i 马克互换。
// 选择何时换汇，最后一天结束前全部换回美元。
// 输出能得到的最大美元金额，保留两位小数。
// 数据范围：1 ≤ N ≤ 100，1 ≤ A_i ≤ 1000，
// 允许 0.05 美元的误差。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划

#include<stdio.h>

double max(double a,double b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    double nums[n+1];
    for(int i=1;i<=n;i++)
        scanf("%lf",&nums[i]);
    double dp[n+1][2];
    dp[1][0]=100;
    dp[1][1]=nums[1];
    for(int i=2;i<=n;i++)
    {
        dp[i][0]=max(dp[i-1][0],dp[i-1][1]*100/nums[i]);
        dp[i][1]=max(dp[i-1][1],dp[i-1][0]*nums[i]/100.0);
    }
    printf("%.2lf\n",max(dp[n][0],dp[n][1]*100/nums[n]));
    return 0;
}
