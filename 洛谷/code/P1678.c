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
