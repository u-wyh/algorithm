#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],sum[n+1];
    sum[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum[i]=a[i]+sum[i-1];
    }
    long long  ans=0;
    for(int i=2;i<=n;i++){
        if(sum[i]>0)
            ans+=sum[i];
    }
    printf("%lld\n",ans);
    return 0;
}

