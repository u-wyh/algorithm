// https://www.luogu.com.cn/problem/P3558
// 题意：输入序列长度 n，以及只含 -1, 0, 1 的序列 x_1..x_n。
// 每次操作可选 1 <= i < n，
// 将 x_{i+1} 变为 x_{i+1} + x_i，
// 求把序列变成单调不降的最少操作次数。
// 输出最少操作次数，若无解输出 BRAK。
// 数据范围：1 <= n <= 10^6，x_i in {-1, 0, 1}。
// 难度评分：1800（洛谷分级换算）
// 算法标签：线性动态规划、滚动数组
#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int x;
    scanf("%d",&x);
    int dp[3]={1e9,1e9,1e9};
    dp[x+1]=0;
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&x);
        if(x==-1)
        {
            dp[1]=1e9;
            dp[2]+=2;
        }
        if(x==0)
        {
            dp[1]=min(dp[1],dp[0]);
            dp[0]++;
            dp[2]++;
        }
        if(x==1)
        {
            dp[2]=min(dp[2],min(dp[1],dp[0]));
            dp[1]=dp[0]+1;
            dp[0]+=2;
        }
    }
    int ans=min(dp[0],min(dp[1],dp[2]));
    if(ans>=1e9)
        printf("BRAK\n");
    else
        printf("%d\n",ans);
    return 0;
}

