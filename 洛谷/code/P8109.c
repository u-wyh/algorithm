#include<stdio.h>

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[n-i+1]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[n-i+1]);
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=min(a[i],b[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
