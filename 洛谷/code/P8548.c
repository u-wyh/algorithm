#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[n+1],c[n+1];
    int sum1=0,sum2=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
        sum1+=a[i];
        sum2+=b[i];
    }
    return 0;
}
