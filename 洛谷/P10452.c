#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=abs(a[i]-a[n/2+1]);
    }
    printf("%lld\n",ans);
    return 0;
}
