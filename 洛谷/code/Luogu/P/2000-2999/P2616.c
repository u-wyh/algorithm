#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b,e;
}shop;

int cmp(const void *a,const void *b)
{
    shop * sa=(shop *)a;
    shop * sb=(shop *)b;
    return sa->b-sb->b;
}
int main()
{
    int m,k,n;
    scanf("%d %d %d",&m,&k,&n);
    shop nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&nums[i].e,&nums[i].a,&nums[i].b);
        nums[i].b+=k-nums[i].e;
    }
    qsort(nums+1,n,sizeof(shop),cmp);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(m>0)
        {
            if(m>=nums[i].a)
            {
                ans+=nums[i].b*nums[i].a;
                m-=nums[i].a;
            }
            else
            {
                ans+=m*nums[i].b;
                m=0;
            }
        }
        else
            break;
    }
    printf("%d\n",ans);
    return 0;
}
