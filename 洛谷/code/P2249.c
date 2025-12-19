#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    while(m--){
        int k;
        scanf("%d",&k);
        int l=1,r=n,mid,ans=-1;
        while(l<=r){
            mid=((r-l)>>1)+l;
            if(nums[mid]>=k){
                if(nums[mid]==k) ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        printf("%d ",ans);
    }
    return 0;
}
