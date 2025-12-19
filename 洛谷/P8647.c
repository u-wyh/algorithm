#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct
{
    int l,w;
}choloate;

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int check(int limit,choloate *nums,int n){
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=((nums[i].l/limit)*(nums[i].w/limit));
    }
    return ans;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    choloate nums[n+1];
    int l=1,r=0,mid,ans=1;
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].l,&nums[i].w);
        r=max(r,max(nums[i].l,nums[i].w));
    }
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n)>=k){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
