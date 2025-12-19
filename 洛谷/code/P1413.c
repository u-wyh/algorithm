#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}zombie;

int max(int a,int b)
{
    return a>b?a:b;
}

int cmp(const void *a,const void *b)
{
    zombie *za=(zombie *)a;
    zombie *zb=(zombie *)b;
    if(za->a>zb->a)
        return 1;
    if(za->a<zb->a)
        return -1;
    return za->b-zb->b;
}
int main()
{
    int n;
    scanf("%d",&n);
    zombie nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(zombie),cmp);
    /*for(int i=1;i<=n;i++)
    {
        printf("%d %d\n",nums[i].a,nums[i].b);
    }*/
    int ans=1;
    int x=nums[1].b+59;
    for(int i=2;i<=n;i++)
    {
        if(nums[i].a==nums[i-1].a)
        {
            if(nums[i].b>x)
            {
                ans++;
                x=nums[i].b+59;
            }
        }
        else
        {
            ans++;
            x=nums[i].b+59;
        }
    }
    printf("%d\n",ans);
    return 0;
}
