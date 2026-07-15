#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 100000+5

int n,m;
int nums[MAX];

bool check(int x){
    int ans=1,k=nums[1];
    for(int i=2;i<=n;i++){
        if(nums[i]-k>=x){
            ans++;
            k=nums[i];
        }
        if(ans>=m)
            return true;
    }
    return false;
}

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int l=1,r=nums[n],mid,ans=1;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
