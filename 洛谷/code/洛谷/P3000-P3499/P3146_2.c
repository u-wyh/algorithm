// https://www.luogu.com.cn/problem/P3146
// 题意：输入序列长度 N，以及 N 个正整数。
// 每次操作可以把两个相邻且相等的数合并成一个比原数大 1 的数。
// 不断合并，求最终序列中能出现的最大数值。
// 输出一个整数表示最大数值。
// 数据范围：2 <= N <= 248，初始每个数在 [1, 40] 之间。
// 算法标签：区间动态规划
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int ans=0;
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        ans=max(ans,nums[i]);
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
    {
        dp[i][i]=nums[i];
    }
    for(int len=2;len<=n;len++)
    {
        for(int i=1;i<=n-len+1;i++)
        {
            int j=i+len-1;
            for(int k=i;k<j;k++)
            {
                if(dp[i][k]==dp[k+1][j])
                {
                    dp[i][j] = max(dp[i][j], dp[i][k] + 1);
                    ans = max(ans, dp[i][j]);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
