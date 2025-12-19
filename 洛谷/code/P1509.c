#include<stdio.h>
#include<limits.h>

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
    int rmb[n+1],rp[m+1],time[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&rmb[i],&rp[i],&time[i]);
    }
    int RMB,RP;
    scanf("%d %d",&RMB,&RP);
    return 0;
}
