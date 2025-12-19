#include<stdio.h>
#include<math.h>

long long check(long long  x){
    return x*log10(x)+1;
}

int main()
{
    int n;
    scanf("%d",&n);
    long long  l=1,r=n,mid,ans=n;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)>=n){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
