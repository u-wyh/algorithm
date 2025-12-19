#include<stdio.h>

int main()
{
    int n,a,b;
    scanf("%d %d %d",&n,&a,&b);
    double t;
    t=(1.0*n/(2+1.0*(a-b)/(a+b))/b)+(n-(1.0*n/(2+1.0*(a-b)/(a+b))))/a;
    printf("%.6lf",t);
    return  0;
}
