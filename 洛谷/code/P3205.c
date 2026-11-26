// https://www.luogu.com.cn/problem/P3205
// 题意：输入人数 n，以及一个长度为 n 的理想身高序列 h_1..h_n（所有身高互不相同）。
// 初始队列按任意顺序依次将每人插入当前队形：第 1 人直接放中间；之后每人若比前一个插入的人高则插到当前队形最右端，否则插到最左端。
// 输出有多少种不同的初始排队顺序能得到给定的理想队形，结果对 19650827 取模。
// 数据范围：n <= 1000，1000 <= h_i <= 2000。
#include<stdio.h>
#define MOD 19650827

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[n+1][n+1][2];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j][0]=0;
            dp[i][j][1]=0;
            if(i==j)
                dp[i][j][0]=1;
        }
    }
    for(int len=2;len<=n;len++)
    {
        for(int i=1;i<=n-len+1;i++)
        {
            int j=len+i-1;
            if (nums[i] < nums[i + 1]) {
                dp[i][j][0] = (dp[i][j][0] + dp[i + 1][j][0]) % MOD;
            }
            if (nums[i] < nums[j]) {
                dp[i][j][0] = (dp[i][j][0] + dp[i + 1][j][1]) % MOD;
            }
            if (nums[j] > nums[i]) {
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][0]) % MOD;
            }
            if (nums[j] > nums[j - 1]) {
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][1]) % MOD;
            }
        }
    }
    printf("%d\n", (dp[1][n][0] + dp[1][n][1]) % MOD);
    return 0;
}
