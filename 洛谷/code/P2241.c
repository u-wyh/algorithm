#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    long long ans1=0,ans2=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i==j){
                ans1+=(n-i+1)*(m-j+1);
            }else{
                ans2+=(n-i+1)*(m-j+1);
            }
        }
    }
    printf("%lld %lld\n",ans1,ans2);
    return 0;
}
