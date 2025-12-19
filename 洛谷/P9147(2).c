#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int ans=1;
    int nums[n+1];
    int start[n+1],end[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    for(int i=0;i<=n;i++)
    {
        start[i]=1;
        end[i]=1;
    }
    for(int i=n-1;i>=1;i--)
    {
        if(nums[i]<nums[i+1])
            start[i]=start[i+1]+1;
        ans=max(ans,start[i]);
    }
    for(int i=2;i<=n;i++)
    {
        if(nums[i]>nums[i-1])
            end[i]=end[i-1]+1;
        ans=max(ans,end[i]);
    }
    ans+=1;
    for(int i=2;i<=n-1;i++)
    {
        if(nums[i-1]+1<nums[i+1])
            ans=max(ans,start[i+1]+end[i-1]+1);
    }
    printf("%d\n",ans>n?n:ans);
    return 0;
}
