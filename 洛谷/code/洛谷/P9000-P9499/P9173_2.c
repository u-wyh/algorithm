// https://www.luogu.com.cn/problem/P9173
// 题意：给定两个长度分别为 n 和 m 的 01 数组，
// 将每个 0 替换为正偶数、每个 1 替换为正奇数，
// 要求替换后两个数组均严格单调递增
// 且所有正整数至多使用一次。
// 最小化使用的最大数字并输出。
// 数据范围：0 <= n, m <= 5000。
// 算法标签：动态规划
#include<stdio.h>
#include<limits.h>
#define Max 5005

int dp[Max][Max][2];

int min(int a,int b)
{
    return a<b?a:b;
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d",&n);
    int a[n+1];
    a[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    int b[m+1];
    b[0]=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&b[i]);
    }
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            if (i==0 && j==0) continue;
            dp[i][j][0]=1e9;
            if(i!=0)
            {
                dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][0]+(a[i]==a[i-1])?2:1);
                dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][1]+(a[i]==b[j])?2:1);
            }
            dp[i][j][1]=1e9;
            if(j!=0)
            {
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+(a[i]==b[j])?2:1);
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+(b[j]==b[j-1])?2:1);
            }
        }
    }
    printf("%d\n",min(dp[n][m][0],dp[n][m][1]));
    return 0;
}
