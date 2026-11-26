// https://www.luogu.com.cn/problem/P1614
// 题意：输入长为 n 的正整数序列 a_i 和整数 m。
// 求所有连续 m 个元素的和的最小值，输出该最小值。
// 数据范围：
// 0 <= m <= n <= 3*10^3（序列长与区间长）
// 1 <= a_i <= 100（刺痛值）
#include<stdio.h>

long long min(long long  a,long long  b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    long long sum[n+1],ans=1e9;
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum[i]=sum[i-1]+nums[i];
    }
    for(int i=m;i<=n;i++)
    {
        ans=min(ans,sum[i]-sum[i-m]);
    }
    printf("%lld\n",ans);
    return 0;
}
