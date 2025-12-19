#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m,count=0;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    //printf("%d\n",nums[n]);
    for(int i=2;i<=n-1;i++)
    {
        if(nums[i+1]-nums[i-1]<=m)
        {
            nums[i]=nums[i-1];
            count++;
        }
    }
    printf("%d\n",count);
    return 0;
}
