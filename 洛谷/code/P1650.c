#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int cmp(const void *pa,const void *pb)
{
    int* a=(int *)pa;
    int* b=(int *)pb;
    return *b-*a;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&b[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,n,sizeof(int),cmp);
    int g[n+1][n+1];
    return 0;
}
