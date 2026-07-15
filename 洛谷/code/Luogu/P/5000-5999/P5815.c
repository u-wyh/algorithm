#include<stdio.h>
#include<stdbool.h>

bool check(long long x,int *nums,int n,int m){
    for(int i=1;i<=n;i++){
        if(nums[i]<x){
            m-=(x-nums[i]);
        }
        if(m<0)
            return false;
    }
    return true;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    long long  l=0,r=1e10,mid,ans;
    while(l<=r){
        mid=((r-l)>>1)+l;
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
