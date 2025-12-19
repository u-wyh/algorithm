#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
    {
    int n;
    scanf("%d",&n);
    int nums[n+1],ans=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        if(nums[i]==1)
            ans++;
        else
            nums[i]=1;
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        printf("%d ",nums[i]);
    printf("\n");
    }
    return 0;
}
