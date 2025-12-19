#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}game;

int cmp(const void *a,const void *b)
{
    game * ga=(game *)a;
    game * gb=(game *)b;

    /*if(ga->a > gb->a)
        return 1;
    if(ga->a < gb->a)
        return -1;*/

    return gb->b - ga->b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    game nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i].a);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i].b);
        m-=nums[i].b;
    }
    qsort(nums+1,n,sizeof(game),cmp);

    for(int i=1;i<=n;i++)
    {
        printf("%d %d\n",nums[i].a,nums[i].b);
    }

    int k=1;
    for(int i=1;i<=n;i++)
    {
        if(k<=nums[i].a)
        {
            k++;
            m+=nums[i].b;
        }
    }
    printf("%d\n",m);
    return 0;
}
