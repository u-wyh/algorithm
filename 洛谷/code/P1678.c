// https://www.luogu.com.cn/problem/P1678
// 题意：输入 m 所学校的预计分数线 a_i 和 n 名学生的估分 b_i。
// 为每位学生选一所分数线与估分之差绝对值最小的学校。
// 求所有学生最小绝对差之和并输出。
// 数据范围：
// 1 <= n, m <= 10^5（学生数与学校数）
// 0 <= a_i, b_i <= 10^6（分数线与估分）
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    for(int j=1;j<=m;j++)
    {
        scanf("%d",&b[i]);
    }
    qsort(b+1,m,sizeof(int),cmp);
    int k=1;
    for(int i=1;i<=m;i++)
    {

    }
    return 0;
}
