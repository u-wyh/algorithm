#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int max=0,sum=0,k=nums[1];
    for(int i=1;i<=n;i++)
    {
        k=k>nums[i]?k:nums[i];
        sum+=nums[i];
        if(max<sum)
            max=sum;
        if(sum<0)
            sum=0;
    }
    if(k<0)
    {
        printf("%d\n",k);
        return 0;
    }
    printf("%d\n",max);
    return 0;
}
