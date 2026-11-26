// https://www.luogu.com.cn/problem/P8786
// 题意：输入整数 N 和 M；
// 初始有 2 斗酒，依次经历 N 次遇店（酒量翻倍，0 斗翻倍仍为 0）和 M 次遇花（喝 1 斗，0 斗时遇花非法）
// 要求最后一次是遇花且恰好喝光为 0 斗，输出合法的遇店与遇花顺序种数对 10^9+7 取模的结果。
// 数据范围：1 <= N, M <= 100。
#include<stdio.h>
#define mod 1000000007

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int dp[n+m+1][m+1][m+1];
    for(int i=0;i<=n+m;i++)
    {
        for(int j=0;j<=m;j++)
        {
            for(int k=0;k<=m;k++)
            {
                dp[i][j][k]=0;
            }
        }
    }
    dp[0][0][2]=1;
    for(int i=0;i< m+n;i++)
    {
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<=m;k++)
            {
                if(dp[i][j][k])
                {
                    if (k > 0)
                        dp[i + 1][j + 1][k - 1] = (dp[i + 1][j + 1][k - 1] + dp[i][j][k]) % mod;
                    if(k<=50)
                        dp[i + 1][j][k * 2] = (dp[i + 1][j][k * 2] + dp[i][j][k]) % mod;
                }
            }
        }
    }
    printf("%d\n",dp[m+n][m][0]);
    return 0;
}
