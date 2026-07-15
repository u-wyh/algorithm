#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    if(n/4<n%4)
    {
        printf("0\n");
        return 0;
    }
    printf("%d\n",(n/4-n%4)/5+1);
    return 0;
}
