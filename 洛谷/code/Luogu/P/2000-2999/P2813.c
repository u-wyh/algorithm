#include<stdio.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&b[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    int t=1;
    for(int i=1;i<=m;i++)
    {
        while(a[t]==0)
            t++;
        if(a[t]<b[i])
        {
            t++;
            b[i]=0;
        }
    }
    long long ans=0;
    if(t<=n)
        printf("0\n");
    else
    {
        for(int i=1;i<=m;i++)
            ans+=b[i];
        printf("%lld\n",ans);
    }
    return 0;
}
