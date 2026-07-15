#include<stdio.h>
#include<stdlib.h>

int check(int x,int *nums,int n,int m){
    int sum=0;
    for(int i=1;i<=n;i++){
        if(sum>=m)
            return sum;
        sum+=(nums[i]>x)?(nums[i]-x):0;
    }
    return sum;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1],max=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        max=max>nums[i]?max:nums[i];
    }
    int l=0,r=max,mid,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n,m)>=m){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
