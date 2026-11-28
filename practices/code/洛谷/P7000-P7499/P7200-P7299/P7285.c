// https://www.luogu.com.cn/problem/P7285
// 题意：T 组数据，每组给定长为 n 的 01 数组，
// 可将若干个 0 改为 1（记修改数为 y，改后最长连续 1 段长为 x）
// 求 x - y 的最大值并构造修改后的数组。
// 数据范围：T <= 10，1 <= n <= 10^5，
// 数组元素 in {0, 1}。
// 难度评分：800（洛谷分级换算）
// 算法标签：贪心、构造
#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
    {
    int n;
    scanf("%d",&n);
    int nums[n+1],ans=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        if(nums[i]==1)
            ans++;
        else
            nums[i]=1;
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        printf("%d ",nums[i]);
    printf("\n");
    }
    return 0;
}
