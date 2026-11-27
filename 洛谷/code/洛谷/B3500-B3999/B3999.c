// https://www.luogu.com.cn/problem/B3999
// 题意：有 n 台机器和 n 笔订单。
// 每天用一台未用过的机器生产，并交付一笔未交付的订单，剩余锣鼓可以留到以后。
// 无解输出 No，有解输出 Yes 和每天使用的机器编号、交付的订单编号。
// 数据范围：1 ≤ T ≤ 10，1 ≤ n ≤ 1000，
// 1 ≤ a[i], b[i] ≤ 10^4。
// 算法标签：贪心、排序

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
