// https://www.luogu.com.cn/problem/P3558
// 题意：输入序列长度 n，以及只含 -1, 0, 1 的序列 x_1..x_n。
// 每次操作可选 1 <= i < n，将 x_{i+1} 变为 x_{i+1} + x_i，求把序列变成单调不降的最少操作次数。
// 输出最少操作次数，若无解输出 BRAK。
// 数据范围：1 <= n <= 10^6，x_i in {-1, 0, 1}。
#include<stdio.h>
// 算法标签：线性动态规划


int min(int a,int b)
{
    return a<b?a:b;
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
    int dp[n+1][3];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<3;j++)
        {
            dp[i][j]=1e9;
        }
    }
    dp[1][nums[1]+1]=0;
    for(int i=2;i<=n;i++)
    {
        if(nums[i]==-1)
        {
            dp[i][0]=dp[i-1][0];
            dp[i][2]=dp[i-1][2]+2;
        }
        if(nums[i]==0)
        {
            dp[i][0]=dp[i-1][0]+1;
            dp[i][1]=min(dp[i-1][1],dp[i-1][0]);
            dp[i][2]=dp[i-1][2]+1;
        }
        if(nums[i]==1)
        {
            dp[i][0]=dp[i-1][0]+2;
            dp[i][1]=dp[i-1][0]+1;
            dp[i][2]=min(dp[i-1][2],min(dp[i-1][0],dp[i-1][1]));
        }
    }
    int ans=min(dp[n][0],min(dp[n][1],dp[n][2]));
    if(ans>=1e9)
        printf("BRAK\n");
    else
        printf("%d\n",ans);
    return 0;
}
