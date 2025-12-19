#include<stdio.h>

int main()
{
    long long n;
    scanf("%lld",&n);
    long long l=0,r=100000,mid,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if((mid*mid*mid)<=n){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
