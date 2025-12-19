#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    long long ans=0;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        if(i!=0)
            ans+=max(a[i],a[i-1]);
    }
    printf("%lld\n",ans);
    return 0;
}
