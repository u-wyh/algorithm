#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}work;

int cmp1(const void *a,const void *b)
{
    work *wa=(work *)a;
    work *wb=(work *)b;

    return wb->a - wa->a;
}

int cmp2(const void *a,const void *b)
{
    work *wa=(work *)a;
    work *wb=(work *)b;

    return wa->a - wb->a;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
    {
        int n;
        scanf("%d",&n);
        work a[n+1],b[n+1];
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].a);
            a[i].b=i;
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&b[i].a);
            b[i].b=i;
        }
        qsort(a+1,n,sizeof(work),cmp1);
        //printf("%d\n",a[1].a);
        qsort(b+1,n,sizeof(work),cmp2);
        //printf("%d\n",b[1].a);
        int k=0;
        for(int i=1;i<=n;i++)
        {
            if(k<0)
                break;
            else
            {
                k+=a[i].a-b[i].a;
            }
        }
        if(k<0){
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
            for(int i=1;i<=n;i++)
                printf("%d ",a[i].b);
            printf("\n");
            for(int i=1;i<=n;i++)
                printf("%d ",b[i].b);
            printf("\n");
        }
    }
    return 0;
}
