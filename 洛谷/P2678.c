#include<stdio.h>
#include<stdbool.h>

bool check(int limit,int *nums,int k,int m){
    int ans=0,n=k-1;
    for(int i=0;i<=n;){
        int temp=nums[i];
        ans--;
        while(nums[i]-temp<limit){
            i++;
            ans++;
            if(i==n+2)
                break;
        }
    }
    return ans<=m;
}

int main()
{
    int L,n,m;
    scanf("%d %d %d",&L,&n,&m);
    int a[n+2];
    a[0]=0;
    a[n+1]=L;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int l=1,r=L,ans=1,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,a,n+1,m)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
