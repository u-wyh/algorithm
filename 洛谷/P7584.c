#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int max(int a,int b){
    return a>b?a:b;
}

int cmp(const void *a,const void *b){
    return (*(int *)b-*(int *)a);
}

bool check(int x,int *nums,int n){
    int ans=nums[x]+n;
    for(int i=1;i<x;i++){
        if(nums[i]+i>ans)
            return false;
    }
    return true;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int l=1,r=n,mid,ans;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}

