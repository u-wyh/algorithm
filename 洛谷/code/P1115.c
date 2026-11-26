// https://www.luogu.com.cn/problem/P1115
// 题意：给 n 个整数，选一个非空的连续子段，使其元素和最大。输出这个最大和。
// 数据范围：1 ≤ n ≤ 2 × 10^5，-10000 ≤ a[i] ≤ 10000。

#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int max=0,sum=0,k=nums[1];
    for(int i=1;i<=n;i++)
    {
        k=k>nums[i]?k:nums[i];
        sum+=nums[i];
        if(max<sum)
            max=sum;
        if(sum<0)
            sum=0;
    }
    if(k<0)
    {
        printf("%d\n",k);
        return 0;
    }
    printf("%d\n",max);
    return 0;
}
