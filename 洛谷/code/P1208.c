#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}milk;

int cmp(const void *a,const void *b)
{
    milk *ma=(milk *)a;
    milk *mb=(milk *)b;
    return ma->a-mb->a;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    milk nums[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,m,sizeof(milk),cmp);
    //printf("%d %d\n",nums[1].a,nums[1].b);
    long long  ans=0;
    for(int i=1;i<=m;i++)
    {
        if(n>0)
        {
            if(n>nums[i].b)
            {
                n-=nums[i].b;
                ans+=nums[i].b*nums[i].a;
            }
            else
            {
                ans+=n*nums[i].a;
                n=0;
            }
        }
        else
            break;
    }
    printf("%lld\n",ans);
    return 0;
}
