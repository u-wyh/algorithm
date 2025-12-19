#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX 100000+5

int t;
long long n,m,a[MAX],d[MAX];

bool check(long long x){
    memset(d,0,sizeof(d));
    m-=1;
    for(int i=1;i<=n;i++){
        d[i]+=a[i];
        if(d[i]<x){
            //d[i]+=a[i]*((x-d[i]+a[i]-1)/a[i]);
            d[i+1]+=a[i+1]*((x-d[i]+a[i]-1)/a[i]);
            m-=2*((x-d[i]+a[i]-1)/a[i]);
        }else
            continue;
        if(m<0)
            return false;
        m--;
    }
    return true;
}

int main()
{

    scanf("%d",&t);
    while(t--){
        scanf("%lld %lld",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
        }
        long long l=0,r=1e18,mid,ans;
        while(l<=r){
            mid=(l+r)/2;
            if(check(mid)){
                ans=mid;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
