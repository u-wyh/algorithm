#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        long long a[n+1];
        int c[n+1];
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&c[i]);
        }
        if(c[1]==c[n]){
            printf("%lld\n",a[1]+a[n]);
            continue;
        }
        long long ans=4000000000;
        for(int i=1;i<n;i++){
            if(c[i]==c[1]&&c[i+1]==c[n]){
                ans=ans<(a[i]+a[1]+a[i+1]+a[n])?ans:(a[i]+a[1]+a[i+1]+a[n]);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
