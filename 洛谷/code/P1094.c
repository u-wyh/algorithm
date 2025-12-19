#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a ,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int ),cmp);
    int left=1,right=n,ans=0;
    while(left<=right)
    {
        if(nums[left]+nums[right]<=m)
        {
            left++;
            right--;
            ans++;
        }
        else
        {
            right--;
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
