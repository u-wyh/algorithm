#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b,c;
}time;

int min(int a,int b)
{
    return a<b?a:b;
}

int cmp(const void *a,const void *b)
{
    time *ta=(time *)a;
    time *tb=(time *)b;

    return ta->b - tb->b;
}

int main()
{
    int n;
    scanf("%d",&n);
    time nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
        nums[i].c=nums[i].b-nums[i].a;
    }
    qsort(nums+1,n,sizeof(time),cmp);
    int k=1,ans=1e6;
    for(int i=1;i<=n;i++)
    {
        if(i==1)
        {
            if(nums[1].c<0)
            {
                printf("-1\n");
                return 0;
            }
            else
            {
                ans=min(ans,nums[1].c);
                nums[1].c=nums[1].a;
            }
        }
        else
        {
            if(nums[i].c<nums[i-1].c)
            {
                printf("-1\n");
                return 0;
            }
            else
            {
                ans=min(ans,nums[i].c-nums[i-1].c);
                nums[i].c=nums[i-1].c+nums[i].a;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
