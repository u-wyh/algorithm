// https://www.luogu.com.cn/problem/P8656
// 题意：输入 N, K 和 N 个整数 A_1..A_N，从中选出尽量多的元素（按个体计），使任意被选中的两人积分差的绝对值都不等于 K，输出最多可选人数。
// 数据范围：1 <= N <= 10^5，0 <= K, A_i <= 10^5。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    return 0;
}
