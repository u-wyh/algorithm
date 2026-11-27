// https://www.luogu.com.cn/problem/P2777
// 题意：输入参赛选手数 N，以及 N 位选手此前多日比赛各自的累计得分 B_1..B_N。
// 最后一天有 N 位选手参赛，当天第一名得 N 分、第二名得 N-1 分、……、最后一名得 1 分，无并列排名。
// 问有多少位选手在最后一天比赛结束后仍有可能获得累计总分第一名（允许并列第一，即总分不小于其他所有人）。
// 输出一个整数，表示可能获得最终冠军的选手人数。
// 数据范围：对于 100% 的数据，3 <= N <= 3*10^5，0 <= B_i <= 2*10^6。
#include<stdio.h>
#include<stdlib.h>
// 算法标签：排序、贪心

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    int max=0;
    for(int i=1;i<=n;i++)
    {
        a[i]+=(n-i+1);
        max=max>a[i]?max:a[i];
    }
    int i;
    for(i=1;i<=n;i++)
    {
        if(a[i]+i-1>=max)
            break;
    }
    printf("%d\n",n-i+1);
    return 0;
}
