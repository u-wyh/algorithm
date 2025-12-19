#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct
{
    long long  a,b;
}study;

bool check(long long x,study *nums,int n,int m){
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i].a>=nums[i].b){
            if(nums[i].a*n<x){
                ans+=n;
                ans+=(x-nums[i].a*n+nums[i].b-1)/nums[i].b;
            }else{
                ans+=(x+nums[i].a-1)/nums[i].a;
            }
        }else{
            ans+=(x+nums[i].b-1)/nums[i].b;
        }
        if(ans>n*m)
            return false;
    }
    return true;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    study nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld",&nums[i].a);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&nums[i].b);
    }
    long long l=0,r=1e18,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,nums,n,m)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}

