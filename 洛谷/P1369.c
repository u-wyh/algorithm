#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}rec;

int cmp(const void *a,const void *b)
{
    rec * ra=(rec *)a;
    rec * rb=(rec *)b;

    if(ra->a > rb->a)
        return 1;
    if(ra->a < rb->a)
        return -1;

    return ra->b - rb->b;
}

int main()
{
    int n;
    scanf("%d",&n);
    rec nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(rec),cmp);
    for(int i=1;i<=n;i++){
        printf("%d %d\n",nums[i].a,nums[i].b);
    }
    return 0;
}
