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
