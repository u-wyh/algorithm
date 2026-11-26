// https://www.luogu.com.cn/problem/P2362
// 题意：m 组数据，每组给出 n 根木桩的高度 h_i。
// 求最长不下降子序列的长度 t 及方案总数 c。
// 每组输出一行 t c。
// 数据范围：m <= 5，n <= 20，h_i <= 150。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int nums[151];
        int i=0;
        while(scanf("%d",&nums[++i])==1);
        int n=i;
        printf("%d\n",n);
    }
    return 0;
}
