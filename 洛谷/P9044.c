#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}
int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    //printf("%d\n",nums[1]);
    int i;
    for(i=k+1;i<=n;i++)
    {
        if(nums[i]<nums[k])
            break;
    }
    printf("%d\n",i-1);
    return 0;
}
