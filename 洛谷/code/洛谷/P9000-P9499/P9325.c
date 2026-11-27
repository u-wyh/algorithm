// https://www.luogu.com.cn/problem/P9325
// 题意：给定 N 座山的高度 h_1..h_N。
// 一个区间 [l, r]（1 <= l <= r <= N）的不对称值定义为
// sum_{i=0}^{floor((r-l)/2)} |h_{l+i} -
// h_{r-i}|。
// 对每个长度 k = 1..N，求所有长度为 k 的连续区间中最小的不对称值。
// 题意：第一行输入 N，第二行输入 h_1..h_N；
// 输出一行 N 个整数，第 i 个表示长度为 i 的最小不对称值。
// 数据范围：1 <= N <= 5000，0 <= h_i <= 10^5。
// 算法标签：区间动态规划
#include<stdio.h>
#include<math.h>
#include<limits.h>

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
    long long  dp[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int l=0;l<n;l++)
    {
        long long ans=INT_MAX;
        if(l==0)
            ans=0;
        else
            for(int i=1;i+l<=n;i++)
            {
                int j=i+l;
                dp[i][j]=dp[i+1][j-1]+abs(nums[j]-nums[i]);
                ans=min(dp[i][j],ans);
            }
        printf("%d ",ans);
    }
    return 0;
}
