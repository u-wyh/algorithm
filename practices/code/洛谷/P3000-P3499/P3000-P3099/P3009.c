// https://www.luogu.com.cn/problem/P3009
// 题意：输入营业天数 N，以及每天记录的利润 P_i（可正可负或零）。
// 在这 N 天中选取一段非空连续的时间区间，使得该区间内的每日利润总和最大。
// 计算这个最大的连续子段利润和。
// 输出一行一个整数，表示任意连续时间段利润和的最大值。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，
// |P_i| <= 1000。
// 难度评分：900（洛谷分级换算）
// 算法标签：最大子段和、贪心
#include<stdio.h>
#include<limits.h>
int main()
{
    int n;
    scanf("%d",&n);
    int nums[n];
    int max=0,sum=0,k=INT_MIN;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
        k=nums[i]>k?nums[i]:k;
        sum+=nums[i];
        if(sum>max)
            max=sum;
        if(sum<0)
            sum=0;
    }
    if(max>0)
        printf("%d\n",max);
    else
        printf("%d\n",k);
    return 0;
}
