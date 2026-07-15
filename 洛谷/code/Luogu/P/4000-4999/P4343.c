#include<stdio.h>
#include<stdbool.h>

long long check(long long limit,long long *nums,int n){
    int ans=0;
    long long now=0;
    for(int i=1;i<=n;i++){
        if(now+nums[i]>=limit){
            ans++;
            now=0;
        }else if(now+nums[i]<=0){
            now=0;
        }else{
            now+=nums[i];
        }
    }
    return ans;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    long long nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld",&nums[i]);
    }
    long long l=1,r=1e15,mid,maxans=-1,minans=-1;
    while(l<=r){
        mid=((r-l)>>1)+l;
        if(check(mid,nums,n)>=k){
            if(check(mid,nums,n)==k) maxans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    l=1,r=1e15;
    while(l<=r){
        mid=((r-l)>>1)+l;
        if(check(mid,nums,n)<=k){
            if(check(mid,nums,n)==k) minans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    if(minans==-1)
        printf("-1\n");
    else
        printf("%lld %lld\n",minans,maxans);
    return 0;
}

