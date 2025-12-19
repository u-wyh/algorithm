#include<stdio.h>
#include<math.h>

int main()
{
    int a[21];
    a[0]=1;
    for(int i=1;i<=20;i++){
        a[i]=pow(2,i-1);
    }
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        long long m,ans1;
        scanf("%d %lld",&n,&m);
        int l=0,r=n,mid=0,ans=0;
        while(l<=r){
            mid=(l+r)/2;
            if(m%a[mid]==0){
                ans=mid;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        //printf("%d\n",ans);
        ans1=a[n-ans]*m;
        printf("%lld\n",ans1);
    }
    return 0;
}
