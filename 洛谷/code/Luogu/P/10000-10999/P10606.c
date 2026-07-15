#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int max=0,a[m+1],b[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        max=max>a[i]?max:a[i];
    }
    int ans=1e9;
    for(int i=max;i<=n;i++)
    {
        ans=min(ans,nums[i]);
    }
    printf("%d\n",ans);
    return 0;
}
