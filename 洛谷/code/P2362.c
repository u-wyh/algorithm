#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int nums[151];
        int i=0;
        while(scanf("%d",&nums[++i])==1);
        int n=i;
        printf("%d\n",n);
    }
    return 0;
}
