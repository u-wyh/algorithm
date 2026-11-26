// https://www.luogu.com.cn/problem/P9517
// 题意：有 n 个瓶子排成一排，a_i ∈ {0, 1} 表示第 i 个瓶子是否装着水（1 有水，0 空）。
// 只能选择一对 l <= r，拿起区间 [l, r] 内所有瓶子喝光全部水。
// 求至少需要拿起多少个瓶子（若本就无水则为 0）。
// 题意：第一行输入 n，第二行输入 a_1..a_n；输出一行一个整数。
// 数据范围：1 <= n <= 10^5，0 <= a_i <= 1。
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int min=n,max=n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    for(int i=1;i<=n;i++)
    {
        if(nums[i]==1)
        {
            min=i;
            break;
        }
    }
    for(int i=n;i>=1;i--)
    {
        if(nums[i]==1)
        {
            max=i;
            break;
        }
    }
    if(max!=min)
        printf("%d\n",max-min+1);
    else
        printf("0\n");
    return 0;
}
