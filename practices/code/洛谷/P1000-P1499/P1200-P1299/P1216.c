// https://www.luogu.com.cn/problem/P1216
// 题意：给一个数字三角形。从顶点走到最后一行，每步到下一行的左下或右下相邻位置。
// 输出整条路径经过数字之和的最大值。
// 数据范围：1 ≤ r ≤ 1000，各位置上的数在 [0,100]。
// 算法标签：动态规划

#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1][n+1];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    int dp[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
        dp[n][i]=nums[n][i];
    for(int i=n-1;i>=1;i--)
    {
        for(int j=1;j<=i;j++)
        {
            dp[i][j]=nums[i][j]+max(dp[i+1][j],dp[i+1][j+1]);
        }
    }
    printf("%d\n",dp[1][1]);
    return 0;
}
