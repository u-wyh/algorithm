#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int b[n+1];
    int ans=0;
    for(int i=0;i<=1;i++)
    {
        int f=1;
        b[1]=i;
        b[2]=a[1]-b[1];
        if(b[2]!=0&&b[2]!=1)
            f=0;
        for(int j=3;j<=n;j++)
        {
            b[j]=a[j-1]-b[j-1]-b[j-2];
            if(b[j]!=1&&b[j]!=0)
                f=0;
        }
        if(b[n]!=a[n]-b[n-1])
            f=0;
        ans+=f;
    }
    printf("%d\n",ans);
    return 0;
}
