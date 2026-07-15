#include<stdio.h>
#include<stdlib.h>
#define Max 1000+5

int used[Max];

typedef struct
{
    int a,b,c;
}num;

int cmp(const void *a,const void *b)
{
    num * na=(num *)a;
    num * nb=(num *)b;

    if(na->b > nb->b)
        return 1;
    if(na->b < nb->b)
        return -1;

    return (nb->a - na->a);
}

int main()
{
    int n;
    scanf("%d",&n);
    int max=0;
    num nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d %d",&nums[i].a,&nums[i].b,&nums[i].c);
        max=max>nums[i].b?max:nums[i].b;
    }
    qsort(nums+1,n,sizeof(num),cmp);
    for(int i=nums[1].b,j=1;j<=nums[1].c;j++,i--)
    {
        used[i]=1;
    }
    for(int i=2;i<=n;i++)
    {
        int count=0;
        for(int j=nums[i].a;j<=nums[i].b;j++)
        {
            if(used[j]==1)
                count++;
        }
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
    for(int i=1;i<=max;i++)
    {
        ans+=used[i];
    }
    printf("%d\n",ans);
    return 0;
}
