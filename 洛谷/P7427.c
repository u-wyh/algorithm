#include<stdio.h>
#include<math.h>

int main()
{
    long long a,b,n;
    scanf("%lld %lld",&a,&b);
    n=sqrt(2*(a+b));
    if(n*(n+1)!=2*(a+b)){
        printf("No\n");
        return 0;
    }
    printf("%lld ",n);
    for(int i=n;i>=1;i--){
        if(a>i){
            a-=i;
            printf("%d ",i);
        }
        else if(a==i){
            printf("%d",i);
            break;
        }
    }
    return 0;
}
