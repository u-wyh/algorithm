#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int k=1;k<=t;k++)
    {
        long long a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        if(a>c||(a*(2*c-1-a)/2+(c-a))<b)
        {
            printf("Merry\n");
        }
        else
            printf("Renko\n");
    }
    return 0;
}
