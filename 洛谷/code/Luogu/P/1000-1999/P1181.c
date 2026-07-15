#include<stdio.h>
#include<stdbool.h>

bool check(int limit,int *nums,int n,int m){
    int ans=1,sum=0;
    for(int i=1;i<=n;i++){
        if((sum+nums[i])>m){
            ans++;
            sum=nums[i];
        }else{
            sum+=nums[i];
        }
        if(ans>limit){
            return false;
        }
    }
    return ans<=limit;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    int l=1,r=n,mid,ans=n;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,nums,n,m)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
