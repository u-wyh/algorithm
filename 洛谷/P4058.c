#include<stdio.h>
#include<stdbool.h>

#define MAX 100000000+5

long long  h[MAX],a[MAX];
long long  s,L;
int n;

bool check(long long  x){
    long long  ans=0;
    for(int i=1;i<=n;i++){
        if((a[i]*x+h[i])>=L)
            ans+=(a[i]*x+h[i]);
        if(ans>=s)
            return true;
    }
    return false;
}

int main()
{
    scanf("%d %lld %lld",&n,&s,&L);
    for(int i=1;i<=n;i++){
        scanf("%lld",&h[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    long long l=1,r=1e8,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
