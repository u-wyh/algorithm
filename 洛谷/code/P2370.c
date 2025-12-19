#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int cost[n+1],val[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d %d",&cost[i],&val[i]);

    return 0;
}
