// https://www.luogu.com.cn/problem/P1018
// 题意：给一个长度为 n 的数字串，要在相邻数字之间恰好插入 k 个乘号。
// 保持数字的原顺序，把切出的 k + 1 段各当作一个整数，输出这些整数乘积的最大值。
// 数据范围：6 ≤ n ≤ 40，1 ≤ k ≤ 6，k < n。

#include<stdio.h>
#include<string.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    getchar();
    char str[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%c",&str[i]);
    }
    /*for(int i=1;i<=n;i++)
    {
        printf("%c",str[i]);
    }*/
    return 0;
}
