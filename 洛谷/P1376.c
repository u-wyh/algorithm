#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[n+1];
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        if(i!=1)
        {
            if(a[i]>a[i-1]+m)
                a[i]=a[i-1]+m;
        }
        ans+=a[i]*b[i];
    }
    printf("%lld\n",ans);
    return 0;
}
