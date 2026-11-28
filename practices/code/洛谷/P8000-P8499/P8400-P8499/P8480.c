// https://www.luogu.com.cn/problem/P8480
// 题意：给定长为 n 的整数序列 a_i，进行 m 次操作
// 每次任选一个数 a_i 变为
// a_i+2、a_i-2、a_i*2、floor(a_i/2) 四者之一。
// 求 m 次操作后序列极差（最大值减最小值）的最大值。
// 数据范围：100% 数据满足 2 <= n <= 10^6，
// 1 <= m <= 10，0 <= a_i <= 10^9。
// 难度评分：800（洛谷分级换算）
// 算法标签：贪心
#include<stdio.h>

int main()
{
    long long n,m;
    scanf("%lld %lld",&n,&m);
    long long  nums[n+1],max=0,min=1e9;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&nums[i]);
        max=max>nums[i]?max:nums[i];
        min=min<nums[i]?min:nums[i];
    }
    for(int i=1;i<=m;i++)
    {
        if(max<=2)
            max+=2;
        else
            max*=2;
    }
    printf("%lld\n",max-min);
    return 0;
}
