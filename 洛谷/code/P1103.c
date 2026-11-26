// https://www.luogu.com.cn/problem/P1103
// 题意：给 n 本书的高度和宽度，先按高度从低到高摆好，再拿走恰好 k 本。剩下每对相邻书的宽度差取绝对值并求和，输出能做到的最小和。
// 数据范围：2 ≤ n ≤ 100，1 ≤ k<n，高度、宽度至多 200，所有高度互异。

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct
{
    int h;
    int w;
}book;


int cmp(const void *pa, const void *pb) {
    book *a = (book *)pa;
    book *b = (book *)pb;
    return a->h-b->h;
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    book b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&b[i].h,&b[i].w);
    }
    printf("\n");
    qsort(b+1,n,sizeof(book),cmp);
    for(int i=1;i<=n;i++)
    {
        printf("%d %d\n",b[i].h,b[i].w);
    }
    return 0;
}
