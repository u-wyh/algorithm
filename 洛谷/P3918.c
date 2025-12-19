#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int k,n;
    scanf("%d %d",&k,&n);
    int a[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        if(k-2*i+1>=0)
            ans+=(a[i]*(k-2*i+1));
        else
            break;
    }
    printf("%lld\n",ans);
    return 0;
}
