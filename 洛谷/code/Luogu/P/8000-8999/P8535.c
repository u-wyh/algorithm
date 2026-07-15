#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a=n%5;
    int b=n/5;
    if(a>=3)
    {
        printf("2");
        for(int i=1;i<b;i++)
            printf("1");
    }
    else
    {
        for(int i=1;i<=b;i++)
            printf("1");
    }
    return 0;
}
