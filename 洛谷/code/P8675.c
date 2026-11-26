// https://www.luogu.com.cn/problem/P8675
// 题意：输入 n, m 和从下往上对应第 1..n 层的 n*m 图纸（. 可放，X 不可放，第 0 层默认摆满 m 块）；
// 求放置积木的总方案数（第 0 层上什么都不放也算一种，答案对 10^9+7 取模），要求每块积木正下方必有积木、每层内积木必须连续摆放且不能落在 X 处。
// 数据范围：1 <= n, m <= 100。
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    char str[n+1][m+2];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m+1;j++)
        {
            if(j==m+1)
                str[i][j]='\n';
            scanf("%c",&str[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            printf("%c",str[i][j]);
        }
    }
    return 0;
}
