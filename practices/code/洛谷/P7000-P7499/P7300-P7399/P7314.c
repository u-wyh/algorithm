// https://www.luogu.com.cn/problem/P7314
// 题意：给定长为 N 的整数数组 A
// 求所有长度至少为 2 的区间 [L, R]（L < R）中
// max(A[L..R]) - min(A[L..R]) 的最小值。
// 数据范围：2 <= N <= 10^5，|A_i| < 10^9。
// 难度评分：800（洛谷分级换算）
// 算法标签：贪心
#include<stdio.h>

long long min(long long a,long long b)
{
    return a<b?a:b;
}

long long max(long long a,long long b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    long long nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&nums[i]);
    }
    long long ans=1e9;
    for(int i=2;i<=n;i++)
    {
        ans=min(ans,max(nums[i],nums[i-1])-min(nums[i],nums[i-1]));
    }
    printf("%lld\n",ans);
    return 0;
}
