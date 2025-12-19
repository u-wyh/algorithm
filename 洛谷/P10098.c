#include<stdio.h>

typedef struct
{
    long long  a,b,z;
}power;

long long check(long long mid,power *nums,int n){
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(mid>nums[i].z){
            ans+=(nums[i].b*(mid-nums[i].z)+nums[i].a*nums[i].z);
        }else{
            ans+=(nums[i].a*mid);
        }
    }
    return ans;
}

int main()
{
    int n;
    long long p;
    scanf("%d %lld",&n,&p);
    power nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld %lld %lld",&nums[i].z,&nums[i].a,&nums[i].b);
    }
    long long l=0,r=p,ans=p,mid;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,nums,n)>=p){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
