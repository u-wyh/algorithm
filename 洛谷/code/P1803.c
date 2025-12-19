#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}time;

int cmp(const void *a,const void *b)
{
    time * ta=(time *)a;
    time * tb=(time *)b;
    return ta->b-tb->b;
}

int main()
{
    int n;
    scanf("%d",&n);
    time nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(time),cmp);
    int count=1,last=nums[1].b;
    for(int i=2;i<=n;i++)
    {
        if(nums[i].a>=last)
        {
            count++;
            last=nums[i].b;
        }
    }
    printf("%d\n",count);
    return 0;
}
