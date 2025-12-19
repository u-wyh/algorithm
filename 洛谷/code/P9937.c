#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

bool check(int x,int *nums,int n,int m){
    int k=0;
    for(int i=n;i>=n-x+1;i--){
        if(nums[i]>=x)
            k++;
        else if(nums[i]+1==x&&m>=1){
            m--;
            k++;
        }else{
            break;
        }
    }
    return k>=x;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int l=nums[1],r=nums[n]+m,mid,ans;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n,m)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
