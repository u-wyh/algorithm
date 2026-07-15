#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        long long n,m;
        scanf("%lld %lld",&n,&m);
        long long  k=n/m*(m-1)+((n%m>0)?(n%m-1):0);
        if(k%2==0){
            printf("1\n");
        }else{
            printf("0\n");
        }
    }
    return 0;
}
