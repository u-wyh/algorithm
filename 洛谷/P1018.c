#include<stdio.h>
#include<string.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    getchar();
    char str[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%c",&str[i]);
    }
    /*for(int i=1;i<=n;i++)
    {
        printf("%c",str[i]);
    }*/
    return 0;
}
