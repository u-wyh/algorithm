#include<stdio.h>

long long check(long long x){
    long long ans=0;
    for(long long i=2;i*i*i<=x;i++)
        ans+=x/(i*i*i);
    return ans;
}

int main()
{
    long long n,l=0,r=5e15,ans,mid;
    scanf("%lld",&n);
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)<n){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",check(ans+1)==n?(ans+1):-1);
    return 0;
}
