#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int m,n,r;
    scanf("%d %d %d",&m,&n,&r);
    int start[n+1],end[n+1],eff[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&start[i],&end[i],&eff[i]);
        end[i]+=r;
    }

    return 0;
}
