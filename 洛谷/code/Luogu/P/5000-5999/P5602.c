#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(long long *)b-*(long long *)a);
}

int main()
{
    int n;
    scanf("%d",&n);
    long long a[n+1],sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    qsort(a+1,n,sizeof(long long),cmp);
    double ans=0.0;
    for(int i=1;i<=n;i++)
    {
        if(1.0*(sum+a[i])/i*(sum+a[i])>ans)
        {
            ans=1.0*(sum+a[i])/i*(sum+a[i]);
            sum+=a[i];
        }
        else
            break;
    }
    printf("%.6lf\n",ans);
    return 0;
}
