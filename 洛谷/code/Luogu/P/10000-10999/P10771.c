#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b,c;
}score;

int cmp(const void *a,const void *b)
{
    score *sa=(score *)a;
    score *sb=(score *)b;
    return sa->c - sb->c;
}

int main()
{
    int n,x,y;
    scanf("%d %d %d",&n,&x,&y);
    score nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i].a);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i].b);
        nums[i].c=nums[i].a-nums[i].b;
    }
    qsort(nums+1,n,sizeof(score),cmp);
    //printf("%d\n",nums[1].c);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        if(i<=y)
            ans+=nums[i].b;
        else
            ans+=nums[i].a;
        //printf("%lld\n",ans);
    }
    printf("%lld\n",ans);
    return 0;
}
