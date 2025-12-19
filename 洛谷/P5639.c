#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int ans=0,nums[n+1];
    nums[0]=-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        if(nums[i]!=nums[i-1])
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}
