#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    char str[n+1][m+2];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m+1;j++)
        {
            if(j==m+1)
                str[i][j]='\n';
            scanf("%c",&str[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            printf("%c",str[i][j]);
        }
    }
    return 0;
}
