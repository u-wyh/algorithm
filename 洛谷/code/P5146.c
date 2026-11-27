// https://www.luogu.com.cn/problem/P5146
// 题意：给定长为 n 的整数序列 A，求满足 1 <= i < j <= n 的 A_j - A_i 的最大值。
// 数据范围：2 <= n <= 10^6，A_i 在 int 范围内。
#include<stdio.h>
#include<limits.h>
// 算法标签：模拟

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    long long  nums[n+1],k1=INT_MAX,k2=INT_MIN;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&nums[i]);
        k1=min(k1,nums[i]);
        k2=max(k2,nums[i]);
    }
    printf("%lld\n",k2-k1);
    return 0;
}
