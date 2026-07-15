#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        a[i]=1;
        b[i]=1;
    }
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<i;j++)
        {
            if(nums[i]>nums[j])
                a[i]=max(a[j]+1,a[i]);
        }
    }
    for(int i=n-1;i>=1;i--)
    {
        for(int j=n;j>i;j--)
        {
            if(nums[i]>nums[j])
                b[i]=max(b[i],b[j]+1);
        }
    }
    int ans=n;
    for(int i=1;i<=n;i++)
    {
        ans=min(ans,n-a[i]-b[i]+1);
    }
    printf("%d\n",ans);
    return 0;
}
