#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1][n+1];
    int a[n+1],b[n+1];
    for(int i=0;i<=n;i++)
    {
        a[i]=0;
        b[i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&nums[i][j]);
            a[i]+=nums[i][j];
            b[j]+=nums[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==n)
            continue;
        for(int j=1;j<=n;j++)
        {
            if(b[j]==n)
                continue;
            ans=max(ans,a[i]+b[j]);
        }
    }
    if(ans==0)
        printf("Bad Game!\n");
    else
        printf("%d\n",ans);
    return 0;
}
