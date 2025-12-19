#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[11];
    a[0]=0;
    int b[11]={0,1,3,5,7,9,10,11,14,15,17};
    int c[11];
    for(int i=1;i<=10;i++)
    {
        scanf("%d",&a[i]);
        c[i]=a[i]-b[i];
    }
    return 0;
}
