// https://www.luogu.com.cn/problem/P2132
// 题意：将 n 名身高互异的同学排成 k 排，每排人数不多于后一排且排头对齐。
// 要求每位同学都比正后方及排头方向的同学矮，求合法排列方案数。
// 输出方案数。
// 数据范围：1 <= k <= 5，1 <= n <= 30，方案数小于 2^32。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    return 0;
}
