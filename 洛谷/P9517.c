#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int min=n,max=n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    for(int i=1;i<=n;i++)
    {
        if(nums[i]==1)
        {
            min=i;
            break;
        }
    }
    for(int i=n;i>=1;i--)
    {
        if(nums[i]==1)
        {
            max=i;
            break;
        }
    }
    if(max!=min)
        printf("%d\n",max-min+1);
    else
        printf("0\n");
    return 0;
}
