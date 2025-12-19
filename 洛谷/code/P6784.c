#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
    long long a,b,c,k=0;
    scanf("%lld %lld %lld",&a,&b,&c);
    if((a-b)<=c&&(b-a)<=c)
        k=(a+b+c)/2;
    else
        k=(c+(a<b?a:b));
    //printf("%lld\n",k);
    int ans;
    for(int i=sqrt(2*k);i>=0;i--)
    {
        printf("%d\n",i);
        if((i*(i+1)<=k*2)&&(i*(i+1)>k*2))
        {
            ans=i;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
