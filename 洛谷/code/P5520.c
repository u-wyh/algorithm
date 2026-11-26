// https://www.luogu.com.cn/problem/P5520
// 题意：有 n 个位置和 m 株互不相同的樱花幼苗，要求任意两株幼苗之间至少隔一个空位，求合法种植方案数对 p 取模的结果。
// 输入 type, n, m, p；输出方案数模 p。
// 数据范围：1 <= n <= 2*10^6，1 <= m <= 10^6，1 <= p <= 10^9，1 <= m <= ceil(n/2)。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int type,n,m,mod;
    scanf("%d %d %d %d",&type,&n,&m,&mod);
    return 0;
}
