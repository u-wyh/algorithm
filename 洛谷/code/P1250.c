#include<stdio.h>
#include<stdlib.h>
#define MAX 30000+4

int used[MAX];

typedef struct
{
    int a,b,c;
}tree;

int cmp(const void *a,const void *b)
{
    tree * ta=(tree *)a;
    tree * tb=(tree *)b;

    if(ta->b < tb->b)
        return -1;
    if(ta->b > tb->b)
        return 1;

    return tb->b-ta->b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    tree nums[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&nums[i].a,&nums[i].b,&nums[i].c);
    }
    qsort(nums+1,m,sizeof(tree),cmp);
    /*
    printf("-----------------------------\n");
    for(int i=1;i<=m;i++)
    {
        printf("%d %d %d\n",nums[i].a,nums[i].b,nums[i].c);
    }
    printf("-----------------------------\n");
    */
    for(int i=nums[1].b,j=1;j<=nums[1].c;j++,i--)
    {
        used[i]=1;
    }
    for(int i=2;i<=m;i++)
    {
        int count=0;
        for(int j=nums[i].a;j<=nums[i].b;j++)
        {
            if(used[j]==1)
                count++;
        }
        //printf("%d\n",count);
        if(count>=nums[i].c)
            continue;
        else
        {
            for(int j=nums[i].b,k=1;k<=nums[i].c-count;j--)
            {
                if(used[j]==0)
                {
                    used[j]=1;
                    k++;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=used[i];
    }
    printf("%d\n",ans);
    return 0;
}
