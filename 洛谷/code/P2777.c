#include<stdio.h>
#include<stdlib.h>

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
