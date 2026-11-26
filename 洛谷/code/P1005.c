// https://www.luogu.com.cn/problem/P1005
// 题意：给 n 行 m 列的非负整数矩阵。第 i 轮从每行的左端或右端取一个数，每取一个数就按该数乘以 2^i 计分。共取 m 轮，输出最大总得分。
// 数据范围：1 ≤ n, m ≤ 80，0 ≤ a[i][j] ≤ 1000。

#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1][m+1];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    return 0;
}
