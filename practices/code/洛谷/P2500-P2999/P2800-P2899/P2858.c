// https://www.luogu.com.cn/problem/P2858
// 题意：N 个零食排成一排（价值 v_i），每天只能从队列两端取 1 个卖出。
// 第 a 天卖出收益为 v_i * a，求卖完所有零食的最大总收益。
// 输出最大总收益。
// 数据范围：1 <= N <= 2000，1 <= v_i <= 1000。
// 算法标签：动态规划、区间动态规划
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+2];
    nums[0]=0;
    nums[n+1]=0;
    for(int i=1;i<=n;i++)
        scanf("%d",&nums[i]);
    int dp[n+1][n+2];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n+1;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=n;j>=i;j--)
        {
            int count=n-(j-i+1);
            dp[i][j]=max(dp[i-1][j]+nums[i-1]*count,dp[i][j+1]+count*nums[j+1]);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=max(ans,dp[i][i]+n*nums[i]);
    }
    printf("%d\n",ans);
    return 0;
}
