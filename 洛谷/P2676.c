#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b -*(int *)a);
}

int main()
{
    int n;
    long long m;
    scanf("%d %lld",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    //printf("%d\n",nums[n]);
    int i=1;
    long long sum=0;
    while(sum<m)
    {
        sum+=nums[i++];
    }
    printf("%d\n",i-1);
    return 0;
}
