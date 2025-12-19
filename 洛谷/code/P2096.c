#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1][m+1];
    int b[m+1];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=m;i++)
    {
        b[i]=a[1][i];
        for(int j=2;j<=n;j++)
        {
            b[i]=max(b[i],a[j][i]);
        }
    }
    int Max=0,sum=b[1];
    for(int i=2;i<=m;i++)
    {
        if(sum<0)
            sum=0;
        else
        {
            Max=max(sum,Max);
        }
        sum+=b[i];
    }
    Max=max(sum,Max);
    printf("%d\n",Max);
    return 0;
}
