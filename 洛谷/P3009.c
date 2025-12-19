#include<stdio.h>
#include<limits.h>
int main()
{
    int n;
    scanf("%d",&n);
    int nums[n];
    int max=0,sum=0,k=INT_MIN;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
        k=nums[i]>k?nums[i]:k;
        sum+=nums[i];
        if(sum>max)
            max=sum;
        if(sum<0)
            sum=0;
    }
    if(max>0)
        printf("%d\n",max);
    else
        printf("%d\n",k);
    return 0;
}
