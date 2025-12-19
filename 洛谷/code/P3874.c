#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool check(long long x,int *nums,int n){

}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    long long l=0,r=(n*n-n)/2,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,a,n)){
            l=mid+1;
            ans=mid;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
