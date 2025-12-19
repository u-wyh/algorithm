#include<stdio.h>
#include<math.h>

#define pi 3.1415926535897

int main()
{
    int n;
    scanf("%d",&n);
    double s1,s2;
    s1=pi*pow(n,2);
    printf("%.6lf\n",s1);
    s2=2*pow(n,2);
    printf("%.6lf\n",s2);
    return 0;
}
