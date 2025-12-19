#include<stdio.h>

int main()
{
    int n,t,f,k;
    scanf("%d %d %d",&n,&t,&f);
    k=t-f;
    long long x,a;
    int ans=0;
    for(int i=1;i<=n;i++){
        scanf("%lld %lld",&x,&a);
        if((k+x)>=a){
            ans++;
        }
    }
    printf("%d\n",ans);
}
