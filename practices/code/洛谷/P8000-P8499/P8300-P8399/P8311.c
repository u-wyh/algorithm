// https://www.luogu.com.cn/problem/P8311
// 题意：有 n 个点，
// 在点 a 和点 b 之间修路的长度（代价）为 d_a + d_b，
// 求使所有点连通所需的最小总道路长度（n=1 时为 0）。
// 数据范围：100% 数据满足 1 <= n <= 10^5，
// 1 <= d_i <= 10^9。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、数学
#include<stdio.h>

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1],minans=1e9;
    long long sum=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        minans=min(minans,nums[i]);
        sum+=nums[i];
    }
    sum-=minans;
    sum+=minans*(n-1);
    printf("%lld\n",sum);
    return 0;
}
