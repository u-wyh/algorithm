#include<stdio.h>

int check(int x,int *nums,int n){
    int k=0;
    for(int i=1;i<=n;i++){
        k+=nums[i]/x;
    }
    return k;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    long long sum=0;
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    if(sum<=k){
        printf("0\n");
        return 0;
    }
    int l=1,r=1e8,mid,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n)>=k){
            l=mid+1;
            ans=mid;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
